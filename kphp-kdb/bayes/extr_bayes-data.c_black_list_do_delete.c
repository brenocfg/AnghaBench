#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int text_len; struct TYPE_5__* text; struct TYPE_5__* next; } ;
typedef  TYPE_1__ black_list ;

/* Variables and functions */
 int /*<<< orphan*/  black_list_init (TYPE_1__*) ; 
 int /*<<< orphan*/  qfree (TYPE_1__*,int) ; 

void black_list_do_delete (black_list *bl) {
  black_list *next = bl->next;
  bl->next = bl->next->next;
  qfree (next->text, next->text_len + 1);
  black_list_init (next);
  qfree (next, sizeof (black_list));
}