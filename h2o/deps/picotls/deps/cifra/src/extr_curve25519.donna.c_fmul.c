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
typedef  int /*<<< orphan*/  limb ;

/* Variables and functions */
 int /*<<< orphan*/  fproduct (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  freduce_coefficients (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freduce_degree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
fmul(limb *output, const limb *in, const limb *in2) {
  limb t[19];
  fproduct(t, in, in2);
  /* |t[i]| < 14*2^54 */
  freduce_degree(t);
  freduce_coefficients(t);
  /* |t[i]| < 2^26 */
  memcpy(output, t, sizeof(limb) * 10);
}