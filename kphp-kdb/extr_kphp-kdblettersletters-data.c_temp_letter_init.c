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
struct TYPE_3__ {int id; int drive_l; int priority; struct TYPE_3__* prev; struct TYPE_3__* next; int /*<<< orphan*/ * l; } ;
typedef  TYPE_1__ temp_letter ;

/* Variables and functions */

void temp_letter_init (temp_letter *head_letter) {
  head_letter->id = head_letter->drive_l = head_letter->priority = -1;
  head_letter->l = NULL;
  head_letter->next = head_letter;
  head_letter->prev = head_letter;
}