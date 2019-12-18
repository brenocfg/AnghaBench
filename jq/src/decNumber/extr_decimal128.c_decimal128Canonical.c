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
typedef  int /*<<< orphan*/  decimal128 ;
typedef  int /*<<< orphan*/  decNumber ;
typedef  int /*<<< orphan*/  decContext ;

/* Variables and functions */
 int /*<<< orphan*/  DEC_INIT_DECIMAL128 ; 
 int /*<<< orphan*/  decContextDefault (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decimal128FromNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decimal128ToNumber (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

decimal128 * decimal128Canonical(decimal128 *result, const decimal128 *d128) {
  decNumber dn;                         // work
  decContext dc;                        // ..
  decContextDefault(&dc, DEC_INIT_DECIMAL128);
  decimal128ToNumber(d128, &dn);
  decimal128FromNumber(result, &dn, &dc);// result will now be canonical
  return result;
  }