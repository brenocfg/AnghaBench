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
struct TYPE_3__ {int text_len; int /*<<< orphan*/ * next; int /*<<< orphan*/ * text; } ;
typedef  TYPE_1__ black_list ;

/* Variables and functions */

void black_list_init (black_list *bl) {
  bl->text_len = -1;
  bl->text = NULL;
  bl->next = NULL;
}