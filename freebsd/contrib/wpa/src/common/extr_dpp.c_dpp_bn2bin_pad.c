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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dpp_bn2bin_pad(const BIGNUM *bn, u8 *pos, size_t len)
{
	int num_bytes, offset;

	num_bytes = BN_num_bytes(bn);
	if ((size_t) num_bytes > len)
		return -1;
	offset = len - num_bytes;
	os_memset(pos, 0, offset);
	BN_bn2bin(bn, pos + offset);
	return 0;
}