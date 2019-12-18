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
struct rand_data {scalar_t__ data; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 unsigned int DATA_SIZE_BITS ; 
 int /*<<< orphan*/  MAX_FOLD_LOOP_BIT ; 
 int /*<<< orphan*/  MIN_FOLD_LOOP_BIT ; 
 scalar_t__ jent_loop_shuffle (struct rand_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __u64 jent_lfsr_time(struct rand_data *ec, __u64 time, __u64 loop_cnt)
{
	unsigned int i;
	__u64 j = 0;
	__u64 new = 0;
#define MAX_FOLD_LOOP_BIT 4
#define MIN_FOLD_LOOP_BIT 0
	__u64 fold_loop_cnt =
		jent_loop_shuffle(ec, MAX_FOLD_LOOP_BIT, MIN_FOLD_LOOP_BIT);

	/*
	 * testing purposes -- allow test app to set the counter, not
	 * needed during runtime
	 */
	if (loop_cnt)
		fold_loop_cnt = loop_cnt;
	for (j = 0; j < fold_loop_cnt; j++) {
		new = ec->data;
		for (i = 1; (DATA_SIZE_BITS) >= i; i++) {
			__u64 tmp = time << (DATA_SIZE_BITS - i);

			tmp = tmp >> (DATA_SIZE_BITS - 1);

			/*
			* Fibonacci LSFR with polynomial of
			*  x^64 + x^61 + x^56 + x^31 + x^28 + x^23 + 1 which is
			*  primitive according to
			*   http://poincare.matf.bg.ac.rs/~ezivkovm/publications/primpol1.pdf
			* (the shift values are the polynomial values minus one
			* due to counting bits from 0 to 63). As the current
			* position is always the LSB, the polynomial only needs
			* to shift data in from the left without wrap.
			*/
			tmp ^= ((new >> 63) & 1);
			tmp ^= ((new >> 60) & 1);
			tmp ^= ((new >> 55) & 1);
			tmp ^= ((new >> 30) & 1);
			tmp ^= ((new >> 27) & 1);
			tmp ^= ((new >> 22) & 1);
			new <<= 1;
			new ^= tmp;
		}
	}
	ec->data = new;

	return fold_loop_cnt;
}