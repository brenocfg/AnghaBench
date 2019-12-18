#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {unsigned int sf_size; unsigned int sf_nsec; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*,...) ; 
 int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EFBIG ; 
 unsigned int FLASH_BOOTCFG_MAX_SIZE ; 
 int SF_PAGE_SIZE ; 
 unsigned int SF_SEC_SIZE ; 
 int t4_flash_bootcfg_addr (struct adapter*) ; 
 int t4_flash_erase_sectors (struct adapter*,unsigned int,unsigned int) ; 
 int t4_write_flash (struct adapter*,unsigned int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int t4_load_bootcfg(struct adapter *adap,const u8 *cfg_data, unsigned int size)
{
	int ret, i, n, cfg_addr;
	unsigned int addr;
	unsigned int flash_cfg_start_sec;
	unsigned int sf_sec_size = adap->params.sf_size / adap->params.sf_nsec;

	cfg_addr = t4_flash_bootcfg_addr(adap);
	if (cfg_addr < 0)
		return cfg_addr;

	addr = cfg_addr;
	flash_cfg_start_sec = addr / SF_SEC_SIZE;

	if (size > FLASH_BOOTCFG_MAX_SIZE) {
		CH_ERR(adap, "bootcfg file too large, max is %u bytes\n",
			FLASH_BOOTCFG_MAX_SIZE);
		return -EFBIG;
	}

	i = DIV_ROUND_UP(FLASH_BOOTCFG_MAX_SIZE,/* # of sectors spanned */
			 sf_sec_size);
	ret = t4_flash_erase_sectors(adap, flash_cfg_start_sec,
					flash_cfg_start_sec + i - 1);

	/*
	 * If size == 0 then we're simply erasing the FLASH sectors associated
	 * with the on-adapter OptionROM Configuration File.
	 */
	if (ret || size == 0)
		goto out;

	/* this will write to the flash up to SF_PAGE_SIZE at a time */
	for (i = 0; i< size; i+= SF_PAGE_SIZE) {
		if ( (size - i) <  SF_PAGE_SIZE)
			n = size - i;
		else
			n = SF_PAGE_SIZE;
		ret = t4_write_flash(adap, addr, n, cfg_data, 0);
		if (ret)
			goto out;

		addr += SF_PAGE_SIZE;
		cfg_data += SF_PAGE_SIZE;
	}

out:
	if (ret)
		CH_ERR(adap, "boot config data %s failed %d\n",
				(size == 0 ? "clear" : "download"), ret);
	return ret;
}