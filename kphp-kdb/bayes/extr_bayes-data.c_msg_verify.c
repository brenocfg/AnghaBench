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
struct TYPE_4__ {int random_tag; } ;
typedef  TYPE_1__ message ;

/* Variables and functions */
 int /*<<< orphan*/  msg_free (TYPE_1__*) ; 

int msg_verify (message *msg, int random_tag) {
  if (msg == NULL) {
    return -1;
  }

  if (msg->random_tag != random_tag) {
    //TODO should I really do this?
    msg_free (msg);

    return -1;
  }

  return 0;
}