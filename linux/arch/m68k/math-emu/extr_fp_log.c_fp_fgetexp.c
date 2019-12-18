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
struct fp_ext {scalar_t__ exp; } ;

/* Variables and functions */
 scalar_t__ IS_INF (struct fp_ext*) ; 
 scalar_t__ IS_ZERO (struct fp_ext*) ; 
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fp_conv_long2ext (struct fp_ext*,int) ; 
 int /*<<< orphan*/  fp_monadic_check (struct fp_ext*,struct fp_ext*) ; 
 int /*<<< orphan*/  fp_normalize_ext (struct fp_ext*) ; 
 int /*<<< orphan*/  fp_set_nan (struct fp_ext*) ; 

struct fp_ext *
fp_fgetexp(struct fp_ext *dest, struct fp_ext *src)
{
	dprint(PINSTR, "fgetexp\n");

	fp_monadic_check(dest, src);

	if (IS_INF(dest)) {
		fp_set_nan(dest);
		return dest;
	}
	if (IS_ZERO(dest))
		return dest;

	fp_conv_long2ext(dest, (int)dest->exp - 0x3FFF);

	fp_normalize_ext(dest);

	return dest;
}