#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ decNumberSingle ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_CONTEXT () ; 
 int /*<<< orphan*/  JVP_FLAGS_NUMBER_LITERAL ; 
 scalar_t__ JVP_HAS_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JVP_HAS_KIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_NUMBER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decNumberCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ decNumberIsNegative (int /*<<< orphan*/ *) ; 
 scalar_t__ decNumberIsZero (int /*<<< orphan*/ *) ; 
 double jv_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_dec_number_ptr (int /*<<< orphan*/ ) ; 

int jvp_number_cmp(jv a, jv b) {
  assert(JVP_HAS_KIND(a, JV_KIND_NUMBER));
  assert(JVP_HAS_KIND(b, JV_KIND_NUMBER));

  if(JVP_HAS_FLAGS(a, JVP_FLAGS_NUMBER_LITERAL) && JVP_HAS_FLAGS(b, JVP_FLAGS_NUMBER_LITERAL)) {
    decNumberSingle res; 
    decNumberCompare(&res.number, 
                     jvp_dec_number_ptr(a), 
                     jvp_dec_number_ptr(b),
                     DEC_CONTEXT()
                     );
    if (decNumberIsZero(&res.number)) {
      return 0;
    } else if (decNumberIsNegative(&res.number)) {
      return -1;
    } else {
      return 1;
    }
  } else {
    double da = jv_number_value(a), db = jv_number_value(b);
    if (da < db) {
      return -1;
    } else if (da == db) {
      return 0;
    } else {
      return 1;
    }
  }
}