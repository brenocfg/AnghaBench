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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  crc_t10dif_generic (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crc_t10dif_pcl (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ crypto_simd_usable () ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 

__attribute__((used)) static int __chksum_finup(__u16 crc, const u8 *data, unsigned int len, u8 *out)
{
	if (len >= 16 && crypto_simd_usable()) {
		kernel_fpu_begin();
		*(__u16 *)out = crc_t10dif_pcl(crc, data, len);
		kernel_fpu_end();
	} else
		*(__u16 *)out = crc_t10dif_generic(crc, data, len);
	return 0;
}