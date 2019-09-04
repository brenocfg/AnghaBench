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
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int zend_hash_num_elements (int /*<<< orphan*/ ) ; 

int get_array_size (zval **arr) {
  return zend_hash_num_elements (Z_ARRVAL_P (*arr));
}