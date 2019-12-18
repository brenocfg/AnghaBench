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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int UCD_UCODE_LOAD_BLOCK_NUM ; 
 int UCD_UCODE_LOAD_IDX_DATAX (int) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int,int) ; 
 scalar_t__ roundup (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void write_to_ucd_unit(struct nitrox_device *ndev, u32 ucode_size,
			      u64 *ucode_data, int block_num)
{
	u32 code_size;
	u64 offset, data;
	int i = 0;

	/*
	 * UCD structure
	 *
	 *  -------------
	 *  |    BLK 7  |
	 *  -------------
	 *  |    BLK 6  |
	 *  -------------
	 *  |    ...    |
	 *  -------------
	 *  |    BLK 0  |
	 *  -------------
	 *  Total of 8 blocks, each size 32KB
	 */

	/* set the block number */
	offset = UCD_UCODE_LOAD_BLOCK_NUM;
	nitrox_write_csr(ndev, offset, block_num);

	code_size = ucode_size;
	code_size = roundup(code_size, 8);
	while (code_size) {
		data = ucode_data[i];
		/* write 8 bytes at a time */
		offset = UCD_UCODE_LOAD_IDX_DATAX(i);
		nitrox_write_csr(ndev, offset, data);
		code_size -= 8;
		i++;
	}

	usleep_range(300, 400);
}