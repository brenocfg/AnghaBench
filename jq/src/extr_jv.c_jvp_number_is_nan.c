#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ number; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_2__ jv ;
typedef  int /*<<< orphan*/  decNumber ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_FLAGS_NUMBER_LITERAL ; 
 scalar_t__ JVP_HAS_FLAGS (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JVP_HAS_KIND (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JV_KIND_NUMBER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int decNumberIsNaN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jvp_dec_number_ptr (TYPE_2__) ; 

int jvp_number_is_nan(jv n) {
  assert(JVP_HAS_KIND(n, JV_KIND_NUMBER));

  if (JVP_HAS_FLAGS(n, JVP_FLAGS_NUMBER_LITERAL)) {
    decNumber *pdec = jvp_dec_number_ptr(n);
    return decNumberIsNaN(pdec);
  } else {
    return n.u.number != n.u.number;
  }
}