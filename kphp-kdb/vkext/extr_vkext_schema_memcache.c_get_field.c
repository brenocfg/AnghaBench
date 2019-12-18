#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ **** zval ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ****** (*) (int /*<<< orphan*/ *****,char const*,int)) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ****** (*) (int /*<<< orphan*/ *****,char const*,int)) ; 
 scalar_t__ FAILURE ; 
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ****** (*) (int /*<<< orphan*/ *****,char const*,int)) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *****) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *****) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ******) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ zend_hash_find (int /*<<< orphan*/ ,char*,scalar_t__,void**) ; 
 scalar_t__ zend_hash_index_find (int /*<<< orphan*/ ,int,void*) ; 

zval **get_field (zval *arr, const char *id, int num) {
  ADD_CNT (get_field);
  START_TIMER (get_field);
  assert (arr);
//  fprintf (stderr, "arr = %p, type = %d\n", arr, (int)Z_TYPE_PP (arr));
  if (Z_TYPE_P (arr) != IS_ARRAY) {
//    fprintf (stderr, "=(\n");
    END_TIMER (get_field);
    return 0;
  }
//  fprintf (stderr, ".\n");
//  fprintf (stderr, "%s\n", id);
//  fprintf (stderr, "%d\n", id ?(int) strlen (id) : -2);
  zval **t = 0;
  if (id && strlen (id) && zend_hash_find (Z_ARRVAL_P (arr), (char *) id, strlen (id) + 1, (void **)&t) != FAILURE) {
    assert (t);
    END_TIMER (get_field);
    return t;
  }
  if (zend_hash_index_find (Z_ARRVAL_P (arr), num, (void *)&t) != FAILURE) {
    assert (t);
    END_TIMER (get_field);
    return t;
  }
  END_TIMER (get_field);
  return 0;
}