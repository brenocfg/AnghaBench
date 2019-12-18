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
struct desc_tbl_t {int dummy; } ;
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* tail; struct desc_tbl_t data; } ;
typedef  TYPE_1__ IARTN_Q ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ia_enque_rtn_q (IARTN_Q *que, struct desc_tbl_t data) {
   IARTN_Q *entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
   if (!entry)
      return -ENOMEM;
   entry->data = data;
   entry->next = NULL;
   if (que->next == NULL) 
      que->next = que->tail = entry;
   else {
      que->tail->next = entry;
      que->tail = que->tail->next;
   }      
   return 1;
}