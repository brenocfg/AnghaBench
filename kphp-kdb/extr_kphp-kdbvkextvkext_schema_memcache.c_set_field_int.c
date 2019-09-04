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
 int /*<<< orphan*/  MAKE_STD_ZVAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_long (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  add_index_long (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_field ; 
 scalar_t__ strlen (char const*) ; 

void set_field_int (zval **arr, int val, const char *id, int num) {
  ADD_CNT (set_field);
  START_TIMER (set_field);
  if (!*arr) {
    MAKE_STD_ZVAL (*arr);
    array_init (*arr);
  }
  if (id && strlen (id)) {
    add_assoc_long (*arr, (char *) id, val);
  } else {
    add_index_long (*arr, num, val);
  }
  END_TIMER (set_field);
}