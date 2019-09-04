#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double number; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_NUMBER ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jv_get_kind (TYPE_2__) ; 

double jv_number_value(jv j) {
  assert(jv_get_kind(j) == JV_KIND_NUMBER);
  return j.u.number;
}