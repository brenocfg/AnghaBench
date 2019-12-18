#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  num_decimal; } ;
typedef  TYPE_2__ jvp_literal_number ;
struct TYPE_6__ {scalar_t__ ptr; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_3__ jv ;
typedef  int /*<<< orphan*/  decNumber ;

/* Variables and functions */
 int /*<<< orphan*/  JVP_FLAGS_NUMBER_LITERAL ; 
 int /*<<< orphan*/  JVP_HAS_FLAGS (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static decNumber* jvp_dec_number_ptr(jv j) {
  assert(JVP_HAS_FLAGS(j, JVP_FLAGS_NUMBER_LITERAL));
  return &(((jvp_literal_number*)j.u.ptr)->num_decimal);
}