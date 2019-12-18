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
struct TYPE_4__ {int /*<<< orphan*/ * free_pool; } ;
typedef  TYPE_1__ SCI_ABSTRACT_LIST_T ;
typedef  int /*<<< orphan*/  SCI_ABSTRACT_ELEMENT_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void sci_abstract_list_construct(
   SCI_ABSTRACT_LIST_T         * list,
   SCI_ABSTRACT_ELEMENT_POOL_T * free_pool
)
{
   memset(list, 0, sizeof(SCI_ABSTRACT_LIST_T));
   list->free_pool = free_pool;
}