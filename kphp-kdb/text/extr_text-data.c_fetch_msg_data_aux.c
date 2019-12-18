#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imessage {int flags; TYPE_2__* fmsg; TYPE_1__* msg; } ;
struct TYPE_4__ {int date; int peer_id; } ;
struct TYPE_3__ {int date; int peer_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

int fetch_msg_data_aux (int *A, struct imessage *M, int mode) {
  int i = 0;
  if (mode & 32) {
    A[i++] = M->flags;
  }
  if (M->msg) {
    if (mode & 64) {
      A[i++] = M->msg->date;
    }
    if (mode & 128) {
      A[i++] = M->msg->peer_id;
    }
  } else {
    assert (M->fmsg);
    if (mode & 64) {
      A[i++] = M->fmsg->date;
    }
    if (mode & 128) {
      A[i++] = M->fmsg->peer_id;
    }
  }
  return i;
}