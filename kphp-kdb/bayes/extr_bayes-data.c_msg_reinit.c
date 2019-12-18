#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; int random_tag; scalar_t__* text; } ;
typedef  TYPE_1__ message ;

/* Variables and functions */
 scalar_t__* qrealloc (scalar_t__*,int,int) ; 

int msg_reinit (message *msg, int len, int random_tag) {
  msg->text = qrealloc (msg->text, len + 1, msg->len);
  if (msg->text == NULL) {
    msg->len = 0;
    return -1;
  }

  msg->len = len + 1;
  msg->text[len] = 0;
  msg->random_tag = random_tag;

  return 0;
}