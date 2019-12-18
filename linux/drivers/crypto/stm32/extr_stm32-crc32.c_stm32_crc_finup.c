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
struct shash_desc {int dummy; } ;

/* Variables and functions */
 int stm32_crc_final (struct shash_desc*,int /*<<< orphan*/ *) ; 
 scalar_t__ stm32_crc_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int stm32_crc_finup(struct shash_desc *desc, const u8 *data,
			   unsigned int length, u8 *out)
{
	return stm32_crc_update(desc, data, length) ?:
	       stm32_crc_final(desc, out);
}