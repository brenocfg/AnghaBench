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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (void (*) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int)) ; 
 int /*<<< orphan*/  END_TIMER (void (*) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int)) ; 
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  MAKE_STD_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  START_TIMER (void (*) (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int)) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_PP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_index_zval (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 

void set_field (zval **arr, zval *val, const char *id, int num) {
  ADD_CNT (set_field);
  START_TIMER (set_field);
  if (!*arr) {
    MAKE_STD_ZVAL (*arr);
    array_init (*arr);
  }
  assert (val);
  assert (*arr && Z_TYPE_PP (arr) == IS_ARRAY);
#ifdef VLOG
  fprintf (stderr, "set_field: num:%d val_type:%d arr:%p\n", num, Z_TYPE_P (val), *arr);
#endif
  if (id && strlen (id)) {
    add_assoc_zval (*arr, (char *) id, val);
  } else {
    add_index_zval (*arr, num, val);
  }
  END_TIMER (set_field);
}