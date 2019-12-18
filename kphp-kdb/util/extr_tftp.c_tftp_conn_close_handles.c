#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ h_idx; } ;
struct TYPE_7__ {TYPE_5__ timer; } ;
struct TYPE_6__ {int fd; int /*<<< orphan*/ * name; } ;
struct TYPE_8__ {TYPE_2__ resend; int /*<<< orphan*/ * netascii; int /*<<< orphan*/ * iobuff; TYPE_1__ file; } ;
typedef  TYPE_3__ tftp_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_event_timer (TYPE_5__*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void tftp_conn_close_handles (tftp_connection_t *c) {
  if (c->file.fd >= 0) {
    assert (!close (c->file.fd));
    c->file.fd = -1;
  }
  if (c->file.name) {
    zfree (c->file.name, strlen (c->file.name) + 1);
    c->file.name = NULL;
  }
  if (c->iobuff != NULL) {
    free (c->iobuff);
    c->iobuff = NULL;
  }
  if (c->netascii) {
    free (c->netascii);
    c->netascii = NULL;
  }
  if (c->resend.timer.h_idx) {
    remove_event_timer (&c->resend.timer);
  }
}