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
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct ata_params {int support2; scalar_t__ lba_size48_4; scalar_t__ lba_size48_3; scalar_t__ lba_size48_2; scalar_t__ lba_size48_1; scalar_t__ lba_size_2; scalar_t__ lba_size_1; } ;

/* Variables and functions */
 int ATA_SUPPORT_AMAX_ADDR ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ataama_print(struct ata_params *parm, u_int64_t nativesize, int header)
{
	u_int32_t lbasize = (u_int32_t)parm->lba_size_1 |
				((u_int32_t)parm->lba_size_2 << 16);

	u_int64_t lbasize48 = ((u_int64_t)parm->lba_size48_1) |
				((u_int64_t)parm->lba_size48_2 << 16) |
				((u_int64_t)parm->lba_size48_3 << 32) |
				((u_int64_t)parm->lba_size48_4 << 48);

	if (header) {
		printf("\nFeature                      "
		       "Support  Enabled   Value\n");
	}

	printf("Accessible Max Address Config  ");
	if (parm->support2 & ATA_SUPPORT_AMAX_ADDR) {
		u_int64_t lba = lbasize48 ? lbasize48 : lbasize;
		printf("yes      %s     %ju/%ju\n",
		    (nativesize > lba) ? "yes" : "no ", lba, nativesize);
	} else {
		printf("no\n");
	}
}