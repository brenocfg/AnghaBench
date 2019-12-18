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
struct TYPE_3__ {int nelts; int elt_size; scalar_t__ elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

void
svn_sort__array_delete(apr_array_header_t *arr,
                       int delete_index,
                       int elements_to_delete)
{
  /* Do we have a valid index and are there enough elements? */
  if (delete_index >= 0
      && delete_index < arr->nelts
      && elements_to_delete > 0
      && (arr->nelts - delete_index) >= elements_to_delete)
    {
      /* If we are not deleting a block of elements that extends to the end
         of the array, then we need to move the remaining elements to keep
         the array contiguous. */
      if ((elements_to_delete + delete_index) < arr->nelts)
        memmove(
          arr->elts + arr->elt_size * delete_index,
          arr->elts + (arr->elt_size * (delete_index + elements_to_delete)),
          arr->elt_size * (arr->nelts - elements_to_delete - delete_index));

      /* Delete the last ELEMENTS_TO_DELETE elements. */
      arr->nelts -= elements_to_delete;
    }
}