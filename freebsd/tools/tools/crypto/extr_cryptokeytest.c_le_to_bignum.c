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
 int /*<<< orphan*/ * BN_lebin2bn (void const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static BIGNUM *
le_to_bignum(BIGNUM *res, const void *p, int plen)
{

	res = BN_lebin2bn(p, plen, res);
	if (res == NULL)
		ERR_print_errors_fp(stderr);

	return (res);
}