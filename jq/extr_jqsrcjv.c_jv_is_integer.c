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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ DBL_EPSILON ; 
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ fabs (double) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 double jv_number_value (int /*<<< orphan*/ ) ; 
 double modf (double,double*) ; 

int jv_is_integer(jv j){
  if(jv_get_kind(j) != JV_KIND_NUMBER){
    return 0;
  }
  double x = jv_number_value(j);

  double ipart;
  double fpart = modf(x, &ipart);

  return fabs(fpart) < DBL_EPSILON;
}