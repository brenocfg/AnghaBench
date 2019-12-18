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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
 int RANK_WIDTH_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int numrow(u32 mtr)
{
	int rows = (RANK_WIDTH_BITS(mtr) + 12);

	if (rows < 13 || rows > 18) {
		edac_dbg(0, "Invalid number of rows: %d (should be between 14 and 17) raw value = %x (%04x)\n",
			 rows, (unsigned int)RANK_WIDTH_BITS(mtr), mtr);
		return -EINVAL;
	}

	return 1 << rows;
}