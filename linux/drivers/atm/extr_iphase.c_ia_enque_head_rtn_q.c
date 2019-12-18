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
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* tail; } ;
typedef  TYPE_1__ IARTN_Q ;

/* Variables and functions */

__attribute__((used)) static void ia_enque_head_rtn_q (IARTN_Q *que, IARTN_Q * data) 
{
   data->next = NULL;
   if (que->next == NULL) 
      que->next = que->tail = data;
   else {
      data->next = que->next;
      que->next = data;
   } 
   return;
}