#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ be128 ;

/* Variables and functions */
 int be64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ghash_reflect(u64 h[], const be128 *k)
{
	u64 carry = be64_to_cpu(k->a) >> 63;

	h[0] = (be64_to_cpu(k->b) << 1) | carry;
	h[1] = (be64_to_cpu(k->a) << 1) | (be64_to_cpu(k->b) >> 63);

	if (carry)
		h[1] ^= 0xc200000000000000UL;
}