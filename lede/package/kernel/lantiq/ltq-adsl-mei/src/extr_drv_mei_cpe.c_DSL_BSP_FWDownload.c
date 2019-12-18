#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_6__ {char* address; char* org_address; int size; size_t nCopy; void* type; } ;
typedef  TYPE_2__ smmu_mem_info_t ;
typedef  int /*<<< orphan*/  img_hdr_tmp ;
struct TYPE_8__ {int image_size; int nBar; TYPE_3__* img_hdr; TYPE_2__* adsl_mem_info; } ;
struct TYPE_7__ {unsigned long size; TYPE_1__* page; } ;
struct TYPE_5__ {unsigned long p_offset; } ;
typedef  int DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;
typedef  TYPE_3__ ARC_IMG_HDR ;

/* Variables and functions */
 int DSL_DEV_MEI_ERR_FAILURE ; 
 int DSL_DEV_MEI_ERR_SUCCESS ; 
 TYPE_4__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREE_ALL ; 
 void* FREE_RELOAD ; 
 void* FREE_SHOWTIME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFX_MEI_BarUpdate (int /*<<< orphan*/ *,int) ; 
 int IFX_MEI_DFEMemoryAlloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IFX_MEI_DFEMemoryFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFX_MEI_DMSG (char*) ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*) ; 
 int /*<<< orphan*/  IFX_MEI_HaltArc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_ResetARC (int /*<<< orphan*/ *) ; 
 scalar_t__ KSEG1ADDR (unsigned long) ; 
 int SDRAM_SEGMENT_SIZE ; 
 int XDATA_REGISTER ; 
 int /*<<< orphan*/  copy_from_user (char*,char const*,size_t) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (unsigned long) ; 

DSL_DEV_MeiError_t
DSL_BSP_FWDownload (DSL_DEV_Device_t * pDev, const char *buf,
			 unsigned long size, long *loff, long *current_offset)
{
	ARC_IMG_HDR img_hdr_tmp;
	smmu_mem_info_t *adsl_mem_info = DSL_DEV_PRIVATE(pDev)->adsl_mem_info;

	size_t nRead = 0, nCopy = 0;
	char *mem_ptr;
	char *org_mem_ptr = NULL;
	ssize_t retval = -ENOMEM;
	int idx = 0;

        IFX_MEI_DMSG("\n");

	if (*loff == 0) {
		if (size < sizeof (img_hdr_tmp)) {
			IFX_MEI_EMSG ("Firmware size is too small!\n");
			return retval;
		}
		copy_from_user ((char *) &img_hdr_tmp, buf, sizeof (img_hdr_tmp));
		// header of image_size and crc are not included.
		DSL_DEV_PRIVATE(pDev)->image_size = le32_to_cpu (img_hdr_tmp.size) + 8;

		if (DSL_DEV_PRIVATE(pDev)->image_size > 1024 * 1024) {
			IFX_MEI_EMSG ("Firmware size is too large!\n");
			return retval;
		}
		// check if arc is halt
		IFX_MEI_ResetARC (pDev);
		IFX_MEI_HaltArc (pDev);

		IFX_MEI_DFEMemoryFree (pDev, FREE_ALL);	//free all

		retval = IFX_MEI_DFEMemoryAlloc (pDev,  DSL_DEV_PRIVATE(pDev)->image_size);
		if (retval < 0) {
			IFX_MEI_EMSG ("Error: No memory space left.\n");
			goto error;
		}
		for (idx = 0; idx < retval; idx++) {
			//skip XDATA register
			if (idx == XDATA_REGISTER)
				continue;
			if (idx * SDRAM_SEGMENT_SIZE < le32_to_cpu (img_hdr_tmp.page[0].p_offset))
				adsl_mem_info[idx].type = FREE_RELOAD;
			else
				adsl_mem_info[idx].type = FREE_SHOWTIME;
		}
		DSL_DEV_PRIVATE(pDev)->nBar = retval;

		DSL_DEV_PRIVATE(pDev)->img_hdr =
			(ARC_IMG_HDR *) adsl_mem_info[0].address;

		org_mem_ptr = kmalloc (SDRAM_SEGMENT_SIZE, GFP_KERNEL);
		if (org_mem_ptr == NULL) {
			IFX_MEI_EMSG ("kmalloc memory fail!\n");
			retval = -ENOMEM;
			goto error;
		}
		
		if (((unsigned long)org_mem_ptr) & (1023)) {
			/* Pointer not 1k aligned, so free it and allocate a larger chunk
			 * for further alignment.
			 */
			kfree(org_mem_ptr);
			org_mem_ptr = kmalloc (SDRAM_SEGMENT_SIZE + 1024, GFP_KERNEL);
			if (org_mem_ptr == NULL) {
				IFX_MEI_EMSG ("kmalloc memory fail!\n");
				retval = -ENOMEM;
				goto error;
			}
			adsl_mem_info[XDATA_REGISTER].address =
				(char *) ((unsigned long) (org_mem_ptr + 1023) & ~(1024 -1));
		} else {
			adsl_mem_info[XDATA_REGISTER].address = org_mem_ptr;
		}
		
		adsl_mem_info[XDATA_REGISTER].org_address = org_mem_ptr;
		adsl_mem_info[XDATA_REGISTER].size = SDRAM_SEGMENT_SIZE;

		adsl_mem_info[XDATA_REGISTER].type = FREE_RELOAD;
		IFX_MEI_DMSG("-> IFX_MEI_BarUpdate()\n");
		IFX_MEI_BarUpdate (pDev, (DSL_DEV_PRIVATE(pDev)->nBar));
	}
	else if (DSL_DEV_PRIVATE(pDev)-> image_size == 0) {
		IFX_MEI_EMSG ("Error: Firmware size=0! \n");
		goto error;
	}

	nRead = 0;
	while (nRead < size) {
		long offset = ((long) (*loff) + nRead) % SDRAM_SEGMENT_SIZE;
		idx = (((long) (*loff)) + nRead) / SDRAM_SEGMENT_SIZE;
		mem_ptr = (char *) KSEG1ADDR ((unsigned long) (adsl_mem_info[idx].address) + offset);
		if ((size - nRead + offset) > SDRAM_SEGMENT_SIZE)
			nCopy = SDRAM_SEGMENT_SIZE - offset;
		else
			nCopy = size - nRead;
		copy_from_user (mem_ptr, buf + nRead, nCopy);
		for (offset = 0; offset < (nCopy / 4); offset++) {
			((unsigned long *) mem_ptr)[offset] = le32_to_cpu (((unsigned long *) mem_ptr)[offset]);
		}
		nRead += nCopy;
		adsl_mem_info[idx].nCopy += nCopy;
	}

	*loff += size;
	*current_offset = size;
	return DSL_DEV_MEI_ERR_SUCCESS;
error:
	IFX_MEI_DFEMemoryFree (pDev, FREE_ALL);
	return DSL_DEV_MEI_ERR_FAILURE;
}