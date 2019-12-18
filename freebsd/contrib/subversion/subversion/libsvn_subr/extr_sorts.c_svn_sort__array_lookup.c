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
typedef  int apr_size_t ;
struct TYPE_3__ {int nelts; int elt_size; void const* elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int bsearch_lower_bound (void const*,void*,int,int,int (*) (void const*,void const*)) ; 

void *
svn_sort__array_lookup(const apr_array_header_t *array,
                       const void *key,
                       int *hint,
                       int (*compare_func)(const void *, const void *))
{
  void *result;
  int idx;

  /* If provided, try the index following *HINT (i.e. probably the last
   * hit location) first.  This speeds up linear scans. */
  if (hint)
    {
      /* We intend to insert right behind *HINT.
       * Exit this function early, if we actually can. */
      idx = *hint + 1;
      if (idx >= array->nelts)
        {
          /* We intend to insert after the last entry.
           * That is only allowed if that last entry is smaller than KEY.
           * In that case, there will be no current entry, i.e. we must
           * return NULL. */
          apr_size_t offset;

          *hint = array->nelts;
          if (array->nelts == 0)
            return NULL;

          offset = (array->nelts - 1) * array->elt_size;
          if (compare_func(array->elts + offset, key) < 0)
            return NULL;
        }
      else if (idx > 0)
        {
          /* Intend to insert at a position inside the array, i.e. not
           * at one of the boundaries.  The predecessor must be smaller
           * and the current entry at IDX must be larger than KEY. */
          void *previous;

          *hint = idx;
          previous = array->elts + (idx-1) * array->elt_size;
          result = array->elts + idx * array->elt_size;
          if (compare_func(previous, key) && !compare_func(result, key))
            return result;
        }
      else if (idx <= 0)
        {
          /* Intend to insert at the beginning of an non-empty array.
           * That requires the first entry to be larger than KEY. */
          *hint = 0;
          if (!compare_func(array->elts, key))
            return array->elts;
        }

      /* The HINT did not help. */
    }

  idx = bsearch_lower_bound(key, array->elts, array->nelts, array->elt_size,
                            compare_func);
  if (hint)
    *hint = idx;
  if (idx >= array->nelts)
    return NULL;

  result = array->elts + idx * array->elt_size;
  return compare_func(result, key) ? NULL : result;
}