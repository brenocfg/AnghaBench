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
struct stat {scalar_t__ st_size; } ;
struct fw_block {scalar_t__ addr; scalar_t__ blocklen; scalar_t__ name; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  errmsg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ flash_size ; 
 struct fw_block* fw_blocks ; 
 int fw_num_blocks ; 
 scalar_t__ stat (int /*<<< orphan*/ *,struct stat*) ; 

int
process_files(void)
{
	struct fw_block *b;
	struct stat st;
	int i;

	for (i = 0; i < fw_num_blocks; i++) {
		b = &fw_blocks[i];
		if ((b->addr + b->blocklen) > flash_size) {
			errmsg(0, "block at 0x%08X is too big", b->addr);
			return -1;
		}
		if (b->name == NULL)
			continue;

		if (stat(b->name, &st) < 0) {
			errmsg(0, "stat failed on %s",b->name);
			return -1;
		}
		if (b->blocklen == 0) {
			b->blocklen = flash_size - b->addr;
		}
		if (st.st_size > b->blocklen) {
			errmsg(0,"file %s is too big",b->name);
			return -1;
		}

		b->size = st.st_size;
	}

	return 0;
}