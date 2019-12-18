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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int vli_test_bit (int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static bool vli_is_negative(const u64 *vli, unsigned int ndigits)
{
	return vli_test_bit(vli, ndigits * 64 - 1);
}