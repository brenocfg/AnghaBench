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
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int CUDBG_SF_SECTOR_SIZE ; 
 unsigned int SF_PAGE_SIZE ; 
 int t4_read_flash (struct adapter*,unsigned int,unsigned int,int*,int /*<<< orphan*/ ) ; 

int read_flash(struct adapter *adap, u32 start_sec , void *data, u32 size,
		u32 start_address)
{
	unsigned int addr, i, n;
	int rc;
	u32 *ptr = (u32 *)data;
	addr = start_sec * CUDBG_SF_SECTOR_SIZE + start_address;
	size = size / 4;
	for (i = 0; i < size; i += SF_PAGE_SIZE) {
		if ((size - i) <  SF_PAGE_SIZE)
			n = size - i;
		else
			n = SF_PAGE_SIZE;
		rc = t4_read_flash(adap, addr, n, ptr, 0);
		if (rc)
			goto out;

		addr = addr + (n*4);
		ptr += n;
	}

	return 0;
out:
	return rc;
}