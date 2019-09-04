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
typedef  unsigned long uint32_t ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 unsigned long jvp_string_hash (int /*<<< orphan*/ ) ; 

unsigned long jv_string_hash(jv j) {
  assert(jv_get_kind(j) == JV_KIND_STRING);
  uint32_t hash = jvp_string_hash(j);
  jv_free(j);
  return hash;
}