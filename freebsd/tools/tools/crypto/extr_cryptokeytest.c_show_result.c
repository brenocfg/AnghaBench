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
 int /*<<< orphan*/  BN_print_fp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
show_result(const BIGNUM *a, const BIGNUM *b, const BIGNUM *c,
    const BIGNUM *sw, const BIGNUM *hw)
{
	printf("\n");

	printf("A = ");
	BN_print_fp(stdout, a);
	printf("\n");

	printf("B = ");
	BN_print_fp(stdout, b);
	printf("\n");

	printf("C = ");
	BN_print_fp(stdout, c);
	printf("\n");

	printf("sw= ");
	BN_print_fp(stdout, sw);
	printf("\n");

	printf("hw= ");
	BN_print_fp(stdout, hw);
	printf("\n");

	printf("\n");
}