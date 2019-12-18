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
struct TYPE_4__ {int /*<<< orphan*/ * list; } ;
typedef  scalar_t__ SCI_ITERATOR_HANDLE_T ;
typedef  TYPE_1__ SCI_BASE_ITERATOR_T ;
typedef  int /*<<< orphan*/  SCI_ABSTRACT_LIST_T ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_iterator_first (TYPE_1__*) ; 

void sci_base_iterator_construct(
   SCI_ITERATOR_HANDLE_T   iterator_handle,
   SCI_ABSTRACT_LIST_T   * list
)
{
    SCI_BASE_ITERATOR_T * iterator = (SCI_BASE_ITERATOR_T *) iterator_handle;

    memset(iterator, 0, sizeof(SCI_BASE_ITERATOR_T));
    iterator->list = list;
    sci_iterator_first(iterator);
}