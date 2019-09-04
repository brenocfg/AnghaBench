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
 int /*<<< orphan*/  ADD_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  MAKE_STD_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_PP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  add_assoc_string (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  add_index_string (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  set_field ; 
 scalar_t__ strlen (char const*) ; 

void set_field_string (zval **arr, char *val, const char *id, int num) {
  ADD_CNT (set_field);
  START_TIMER (set_field);
  if (!*arr) {
    MAKE_STD_ZVAL (*arr);
    array_init (*arr);
  }
  assert (val);
  assert (*arr && Z_TYPE_PP (arr) == IS_ARRAY);

  if (id && strlen (id)) {
    add_assoc_string (*arr, (char *) id, val, 1);
  } else {
    add_index_string (*arr, num, val, 1);
  }
  END_TIMER (set_field);
}