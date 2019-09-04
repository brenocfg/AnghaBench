#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int offset; } ;
typedef  TYPE_1__ jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_ARRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jv_get_kind (TYPE_1__) ; 

__attribute__((used)) static int jvp_array_offset(jv a) {
  assert(jv_get_kind(a) == JV_KIND_ARRAY);
  return a.offset;
}