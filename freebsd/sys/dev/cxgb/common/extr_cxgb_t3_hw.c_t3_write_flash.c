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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int EINVAL ; 
 int EIO ; 
 unsigned int SF_PROG_PAGE ; 
 unsigned int SF_SIZE ; 
 unsigned int SF_WR_ENABLE ; 
 int flash_wait_op (int /*<<< orphan*/ *,int,int) ; 
 unsigned int htonl (unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int sf1_write (int /*<<< orphan*/ *,unsigned int,int,unsigned int) ; 
 unsigned int swab32 (unsigned int) ; 
 int t3_read_flash (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int t3_write_flash(adapter_t *adapter, unsigned int addr,
			  unsigned int n, const u8 *data,
			  int byte_oriented)
{
	int ret;
	u32 buf[64];
	unsigned int c, left, val, offset = addr & 0xff;

	if (addr + n > SF_SIZE || offset + n > 256)
		return -EINVAL;

	val = swab32(addr) | SF_PROG_PAGE;

	if ((ret = sf1_write(adapter, 1, 0, SF_WR_ENABLE)) != 0 ||
	    (ret = sf1_write(adapter, 4, 1, val)) != 0)
		return ret;

	for (left = n; left; left -= c) {
		c = min(left, 4U);
		val = *(const u32*)data;
		data += c;
		if (byte_oriented)
			val = htonl(val);

		ret = sf1_write(adapter, c, c != left, val);
		if (ret)
			return ret;
	}
	if ((ret = flash_wait_op(adapter, 5, 1)) != 0)
		return ret;

	/* Read the page to verify the write succeeded */
	ret = t3_read_flash(adapter, addr & ~0xff, ARRAY_SIZE(buf), buf,
			    byte_oriented);
	if (ret)
		return ret;

	if (memcmp(data - n, (u8 *)buf + offset, n))
		return -EIO;
	return 0;
}