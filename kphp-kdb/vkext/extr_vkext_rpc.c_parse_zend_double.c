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
#define  IS_DOUBLE 130 
#define  IS_LONG 129 
#define  IS_STRING 128 
 double Z_DVAL_PP (int /*<<< orphan*/ **) ; 
 double Z_LVAL_PP (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  Z_STRVAL_PP (int /*<<< orphan*/ **) ; 
 int Z_TYPE_PP (int /*<<< orphan*/ **) ; 
 double atof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_double_ex (int /*<<< orphan*/ **) ; 

double parse_zend_double (zval **z) { /* {{{ */
  switch (Z_TYPE_PP (z)) {
  case IS_LONG:
    return Z_LVAL_PP (z);
  case IS_DOUBLE:
    return Z_DVAL_PP (z);
  case IS_STRING:
    return atof (Z_STRVAL_PP (z));
  default:
    convert_to_double_ex (z);
    return Z_DVAL_PP (z);
  }
}