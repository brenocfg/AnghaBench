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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct zyxbcm_tag {int /*<<< orphan*/ * headerCRC; int /*<<< orphan*/ * fskernelCRC; int /*<<< orphan*/ * flashImageEnd; int /*<<< orphan*/ * reserved1; scalar_t__* information1; } ;
struct bcm_tag {int /*<<< orphan*/ * fskernelCRC; int /*<<< orphan*/  kernelLength; int /*<<< orphan*/  flashRootLength; int /*<<< orphan*/  flashImageStart; } ;

/* Variables and functions */
 int ADDRESS_LEN ; 
 int CRC_LEN ; 
 int /*<<< orphan*/  IMAGETAG_CRC_START ; 
 int ZYX_TAGINFO1_LEN ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void fix_header(void *buf)
{
	struct bcm_tag *bcmtag = buf;
	struct zyxbcm_tag *zyxtag = buf;
	uint8_t fskernel_crc[CRC_LEN];
	uint32_t crc;
	uint64_t flash_start, rootfs_len, kernel_len;

	/* Backup values */
	flash_start = strtoul(bcmtag->flashImageStart, NULL, 10);
	rootfs_len = strtoul(bcmtag->flashRootLength, NULL, 10);
	kernel_len = strtoul(bcmtag->kernelLength, NULL, 10);
	memcpy(fskernel_crc, bcmtag->fskernelCRC, CRC_LEN);

	/* Clear values */
	zyxtag->information1[ZYX_TAGINFO1_LEN - 1] = 0;
	memset(zyxtag->flashImageEnd, 0, ADDRESS_LEN);
	memset(zyxtag->fskernelCRC, 0, CRC_LEN);
	memset(zyxtag->reserved1, 0, 2);

	/* Replace values */
	sprintf(zyxtag->flashImageEnd, "%lu", flash_start + rootfs_len + kernel_len);
	memcpy(zyxtag->fskernelCRC, fskernel_crc, CRC_LEN);

	/* Update tag crc */
	crc = htonl(crc32(IMAGETAG_CRC_START, buf, 236));
	memcpy(zyxtag->headerCRC, &crc, 4);
}