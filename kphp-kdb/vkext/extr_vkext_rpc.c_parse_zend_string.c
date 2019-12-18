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
 int Z_STRLEN_PP (int /*<<< orphan*/ **) ; 
 char* Z_STRVAL_PP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  convert_to_string_ex (int /*<<< orphan*/ **) ; 

char *parse_zend_string (zval **z, int *l) { /* {{{ */
  convert_to_string_ex (z);
  if (l) { *l = Z_STRLEN_PP (z); }
  return Z_STRVAL_PP (z);
}