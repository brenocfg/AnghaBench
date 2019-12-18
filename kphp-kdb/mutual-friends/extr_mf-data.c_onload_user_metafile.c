#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int metafile_len; struct aio_connection* aio; int /*<<< orphan*/ * metafile; } ;
typedef  TYPE_1__ user ;
struct connection {int dummy; } ;
struct aio_connection {scalar_t__ basic_type; scalar_t__ extra; } ;

/* Variables and functions */
 int MEMORY_USER_PERCENT ; 
 int /*<<< orphan*/  add_user_used (TYPE_1__*) ; 
 int allocated_metafile_bytes ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bind_user_metafile (TYPE_1__*) ; 
 scalar_t__ ct_aio ; 
 int /*<<< orphan*/  cur_users ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int max_memory ; 
 int /*<<< orphan*/  qfree (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 int user_LRU_unload () ; 
 int verbosity ; 

int onload_user_metafile (struct connection *c, int read_bytes) {
  if (verbosity > 2) {
    fprintf (stderr, "onload_user_metafile(%p,%d)\n", c, read_bytes);
  }

  struct aio_connection *a = (struct aio_connection *)c;
  user *u = (user *) a->extra;

  assert (a->basic_type == ct_aio);
  assert (u != NULL);

  if (u->aio != a) {
    fprintf (stderr, "assertion (u->aio == a) will fail\n");
    fprintf (stderr, "%p != %p\n", u->aio, a);
  }

  assert (u->aio == a);

  if (read_bytes != u->metafile_len) {
    if (verbosity > 0) {
      fprintf (stderr, "ERROR reading user: read %d bytes out of %d: %m\n", read_bytes, u->metafile_len);
    }

    qfree (u->metafile, u->metafile_len);
    allocated_metafile_bytes -= u->metafile_len;
    u->metafile = NULL;
    u->metafile_len = -1;
    u->aio = NULL;
    return 0;
  }
  assert (read_bytes == u->metafile_len);

  if (verbosity > 2) {
    fprintf (stderr, "*** Read user: read %d bytes\n", read_bytes);
  }

  u->aio = NULL;

  bind_user_metafile (u);

  add_user_used (u);
  cur_users++;

  while (allocated_metafile_bytes > max_memory * MEMORY_USER_PERCENT) {
    if (user_LRU_unload() == -1) {
      exit (1);
    }
  }

  return 1;
}