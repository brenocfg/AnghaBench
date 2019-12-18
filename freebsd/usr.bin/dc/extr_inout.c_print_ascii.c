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
struct number {int /*<<< orphan*/  number; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int BN_is_bit_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_negative (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_checkp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 

void
print_ascii(FILE *f, const struct number *n)
{
	BIGNUM *v;
	int ch, i, numbits;

	v = BN_dup(n->number);
	bn_checkp(v);

	if (BN_is_negative(v))
		BN_set_negative(v, 0);

	numbits = BN_num_bytes(v) * 8;
	while (numbits > 0) {
		ch = 0;
		for (i = 0; i < 8; i++)
			ch |= BN_is_bit_set(v, numbits-i-1) << (7 - i);
		putc(ch, f);
		numbits -= 8;
	}
	BN_free(v);
}