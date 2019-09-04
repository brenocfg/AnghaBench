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
typedef  scalar_t__ jv_kind ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  jq_state ;

/* Variables and functions */
 scalar_t__ JV_KIND_NUMBER ; 
 scalar_t__ isnormal (double) ; 
 int /*<<< orphan*/  jv_false () ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 double jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_true () ; 

__attribute__((used)) static jv f_isnormal(jq_state *jq, jv input) {
  jv_kind k = jv_get_kind(input);
  if (k != JV_KIND_NUMBER) {
    jv_free(input);
    return jv_false();
  }
  double n = jv_number_value(input);
  jv_free(input);
  return isnormal(n) ? jv_true() : jv_false();
}