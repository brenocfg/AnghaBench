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
struct TYPE_3__ {int random_tag; scalar_t__ len; int /*<<< orphan*/ * text; } ;
typedef  TYPE_1__ message ;

/* Variables and functions */
 int /*<<< orphan*/  qfree (int /*<<< orphan*/ *,scalar_t__) ; 

void msg_free (message *msg) {
 if (msg->text != NULL) {
    qfree (msg->text, msg->len);
    msg->text = NULL;
  }
  msg->len = 0;
  msg->random_tag = -1;
}