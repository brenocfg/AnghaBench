#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct conn_query {TYPE_4__* cq_type; struct conn_query* next; } ;
struct aiocb {int dummy; } ;
struct aio_connection {int fd; struct aio_connection* cb; struct conn_query* first_query; TYPE_3__* next; TYPE_2__* prev; TYPE_1__* type; int /*<<< orphan*/  last_query; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* close ) (struct conn_query*) ;int /*<<< orphan*/  (* complete ) (struct conn_query*) ;} ;
struct TYPE_7__ {TYPE_2__* prev; } ;
struct TYPE_6__ {TYPE_3__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* wakeup_aio ) (struct connection*,int) ;} ;

/* Variables and functions */
 scalar_t__ AIO_NOTCANCELED ; 
 int EINPROGRESS ; 
 scalar_t__ aio_cancel (int,struct aio_connection*) ; 
 int aio_error (struct aio_connection*) ; 
 scalar_t__ aio_errors_verbosity ; 
 int aio_return (struct aio_connection*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  stub1 (struct connection*,int) ; 
 int /*<<< orphan*/  stub2 (struct conn_query*) ; 
 int /*<<< orphan*/  stub3 (struct conn_query*) ; 
 int verbosity ; 
 int /*<<< orphan*/  zfree (struct aio_connection*,int) ; 

int check_aio_completion (struct aio_connection *a) {

  if (verbosity > 1) {
    fprintf (stderr, "in check_aio_completion(%p [first_query=%p, last_query=%p])\n", a, a->first_query, a->last_query);
  }

  errno = 0;

  int err = aio_error (a->cb);
  
  if (err == EINPROGRESS) {
    if (verbosity > 1) {
      fprintf (stderr, "aio_query %p in progress...\n", a);
    }
    if (a->first_query == (struct conn_query *) a) {
      if (verbosity > 0) {
        fprintf (stderr, "aio_query %p in progress, but all conn_queries are dead, canceling aio.\n", a);
      }
      if (aio_cancel (a->fd, a->cb) == AIO_NOTCANCELED) {
        if (verbosity > 0) {
          fprintf (stderr, "aio_cancel(%d,%p) returns AIO_NOTCANCELED\n", a->fd, a->cb);
        }
        return 0;
      }
      err = aio_error (a->cb);
      if (err == EINPROGRESS) {
        if (verbosity > 0) {
          fprintf (stderr, "aio_query %p still in progress.\n", a);
        }
        return 0;
      }
    } else {
      return 0;
    }
  }

  int res = aio_return (a->cb);
  if (verbosity > 1 || (aio_errors_verbosity && err)) {
    fprintf (stderr, "aio_return() returns %d, errno=%d (%s)\n", res, err, strerror (err));
  }

  a->type->wakeup_aio ((struct connection *)a, res);

  a->next->prev = a->prev;
  a->prev->next = a->next;

  struct conn_query *tmp, *tnext;

  for (tmp = a->first_query; tmp != (struct conn_query *)a; tmp = tnext) {
    tnext = tmp->next;
//    fprintf (stderr, "scanning aio_completion %p,next = %p\n", tmp, tnext);
    if (res >= 0) {
      tmp->cq_type->complete (tmp);
    } else {
      tmp->cq_type->close (tmp);
    }
  }

  if (verbosity > 2) {
    fprintf (stderr, "freeing aio_connection at %p\n", a);
  }

  zfree (a->cb, sizeof (struct aiocb));
  zfree (a, sizeof (struct aio_connection));

  return 1;
}