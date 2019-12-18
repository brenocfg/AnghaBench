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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int bnrand (int,int /*<<< orphan*/ *,int,int,int) ; 

int     BN_pseudo_rand(BIGNUM *rnd, int bits, int top, int bottom)
	{
	return bnrand(1, rnd, bits, top, bottom);
	}