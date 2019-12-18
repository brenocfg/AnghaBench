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
typedef  int u32 ;
struct flash_desc {int member_0; int member_1; int vendor_and_model_id; unsigned int size_mb; } ;
struct TYPE_2__ {unsigned int sf_size; unsigned int sf_nsec; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct flash_desc*) ; 
 int /*<<< orphan*/  A_SF_OP ; 
 int /*<<< orphan*/  CH_WARN (struct adapter*,char*,int,...) ; 
 unsigned int FLASH_MIN_SIZE ; 
 int /*<<< orphan*/  SF_RD_ID ; 
 unsigned int SF_SEC_SIZE ; 
 int sf1_read (struct adapter*,int,int /*<<< orphan*/ ,int,int*) ; 
 int sf1_write (struct adapter*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int t4_get_flash_params(struct adapter *adapter)
{
	/*
	 * Table for non-standard supported Flash parts.  Note, all Flash
	 * parts must have 64KB sectors.
	 */
	static struct flash_desc supported_flash[] = {
		{ 0x00150201, 4 << 20 },	/* Spansion 4MB S25FL032P */
	};

	int ret;
	u32 flashid = 0;
	unsigned int part, manufacturer;
	unsigned int density, size = 0;


	/*
	 * Issue a Read ID Command to the Flash part.  We decode supported
	 * Flash parts and their sizes from this.  There's a newer Query
	 * Command which can retrieve detailed geometry information but many
	 * Flash parts don't support it.
	 */
	ret = sf1_write(adapter, 1, 1, 0, SF_RD_ID);
	if (!ret)
		ret = sf1_read(adapter, 3, 0, 1, &flashid);
	t4_write_reg(adapter, A_SF_OP, 0);	/* unlock SF */
	if (ret < 0)
		return ret;

	/*
	 * Check to see if it's one of our non-standard supported Flash parts.
	 */
	for (part = 0; part < ARRAY_SIZE(supported_flash); part++)
		if (supported_flash[part].vendor_and_model_id == flashid) {
			adapter->params.sf_size =
				supported_flash[part].size_mb;
			adapter->params.sf_nsec =
				adapter->params.sf_size / SF_SEC_SIZE;
			goto found;
		}

	/*
	 * Decode Flash part size.  The code below looks repetative with
	 * common encodings, but that's not guaranteed in the JEDEC
	 * specification for the Read JADEC ID command.  The only thing that
	 * we're guaranteed by the JADEC specification is where the
	 * Manufacturer ID is in the returned result.  After that each
	 * Manufacturer ~could~ encode things completely differently.
	 * Note, all Flash parts must have 64KB sectors.
	 */
	manufacturer = flashid & 0xff;
	switch (manufacturer) {
	case 0x20: /* Micron/Numonix */
		/*
		 * This Density -> Size decoding table is taken from Micron
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x14: size = 1 << 20; break; /*   1MB */
		case 0x15: size = 1 << 21; break; /*   2MB */
		case 0x16: size = 1 << 22; break; /*   4MB */
		case 0x17: size = 1 << 23; break; /*   8MB */
		case 0x18: size = 1 << 24; break; /*  16MB */
		case 0x19: size = 1 << 25; break; /*  32MB */
		case 0x20: size = 1 << 26; break; /*  64MB */
		case 0x21: size = 1 << 27; break; /* 128MB */
		case 0x22: size = 1 << 28; break; /* 256MB */
		}
		break;

	case 0x9d: /* ISSI -- Integrated Silicon Solution, Inc. */
		/*
		 * This Density -> Size decoding table is taken from ISSI
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x16: size = 1 << 25; break; /*  32MB */
		case 0x17: size = 1 << 26; break; /*  64MB */
		}
		break;

	case 0xc2: /* Macronix */
		/*
		 * This Density -> Size decoding table is taken from Macronix
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x17: size = 1 << 23; break; /*   8MB */
		case 0x18: size = 1 << 24; break; /*  16MB */
		}
		break;

	case 0xef: /* Winbond */
		/*
		 * This Density -> Size decoding table is taken from Winbond
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		switch (density) {
		case 0x17: size = 1 << 23; break; /*   8MB */
		case 0x18: size = 1 << 24; break; /*  16MB */
		}
		break;
	}

	/* If we didn't recognize the FLASH part, that's no real issue: the
	 * Hardware/Software contract says that Hardware will _*ALWAYS*_
	 * use a FLASH part which is at least 4MB in size and has 64KB
	 * sectors.  The unrecognized FLASH part is likely to be much larger
	 * than 4MB, but that's all we really need.
	 */
	if (size == 0) {
		CH_WARN(adapter, "Unknown Flash Part, ID = %#x, assuming 4MB\n", flashid);
		size = 1 << 22;
	}

	/*
	 * Store decoded Flash size and fall through into vetting code.
	 */
	adapter->params.sf_size = size;
	adapter->params.sf_nsec = size / SF_SEC_SIZE;

 found:
	/*
	 * We should ~probably~ reject adapters with FLASHes which are too
	 * small but we have some legacy FPGAs with small FLASHes that we'd
	 * still like to use.  So instead we emit a scary message ...
	 */
	if (adapter->params.sf_size < FLASH_MIN_SIZE)
		CH_WARN(adapter, "WARNING: Flash Part ID %#x, size %#x < %#x\n",
			flashid, adapter->params.sf_size, FLASH_MIN_SIZE);

	return 0;
}