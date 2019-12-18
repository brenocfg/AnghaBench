#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct TYPE_4__ {int extension; int command1; int command2; } ;
struct TYPE_3__ {int command2; int command1; int extension; } ;
struct ata_params {int config; int satacapabilities; char* model; char* revision; char* serial; int* wwn; char* product_id; char* media_serial; int cylinders; int heads; int sectors; int capabilities1; int mwdmamodes; int atavalid; int udmamodes; int media_rotation_rate; int support3; int satacapabilities2; int satasupport; int apm_value; int support2; int enabled2; int wrv_mode; int support_dsm; int max_dsm_blocks; int tcg; int multi; TYPE_2__ enabled; TYPE_1__ support; int /*<<< orphan*/  acoustic; int /*<<< orphan*/  queue; int /*<<< orphan*/  version_major; scalar_t__ lba_size48_4; scalar_t__ lba_size48_3; scalar_t__ lba_size48_2; scalar_t__ lba_size48_1; scalar_t__ lba_size_2; scalar_t__ lba_size_1; } ;

/* Variables and functions */
 int ATA_ACOUSTIC_CURRENT (int /*<<< orphan*/ ) ; 
 int ATA_ACOUSTIC_VENDOR (int /*<<< orphan*/ ) ; 
 int ATA_ENCRYPTS_ALL_USER_DATA ; 
 int ATA_FLAG_88 ; 
#define  ATA_PIO1 133 
#define  ATA_PIO2 132 
#define  ATA_PIO3 131 
#define  ATA_PIO4 130 
 int ATA_PROTO_ATAPI ; 
 int ATA_PROTO_CFA ; 
 int ATA_QUEUE_LEN (int /*<<< orphan*/ ) ; 
 int ATA_SATA_GEN1 ; 
 int ATA_SATA_GEN2 ; 
 int ATA_SATA_GEN3 ; 
 int ATA_SUPPORT_64BITWWN ; 
 int ATA_SUPPORT_ADDRESS48 ; 
 int ATA_SUPPORT_ANTIFREEZE_LOCK_EXT ; 
 int ATA_SUPPORT_APM ; 
 int ATA_SUPPORT_AUTOACOUSTIC ; 
 int ATA_SUPPORT_BLOCK_ERASE_EXT ; 
 int ATA_SUPPORT_CFA ; 
 int ATA_SUPPORT_CRYPTO_SCRAMBLE_EXT ; 
 int ATA_SUPPORT_DMA ; 
 int ATA_SUPPORT_DRAT ; 
 int ATA_SUPPORT_DSM_TRIM ; 
 int ATA_SUPPORT_DSN ; 
 int ATA_SUPPORT_EPC ; 
 int ATA_SUPPORT_FLUSHCACHE ; 
 int ATA_SUPPORT_FREEFALL ; 
 int ATA_SUPPORT_GENLOG ; 
 int ATA_SUPPORT_IORDY ; 
 int ATA_SUPPORT_LBA ; 
 int ATA_SUPPORT_LOOKAHEAD ; 
 int ATA_SUPPORT_MEDIASN ; 
 int ATA_SUPPORT_MICROCODE ; 
 int ATA_SUPPORT_NCQ ; 
 int ATA_SUPPORT_NCQ_AUTOSENSE ; 
 int ATA_SUPPORT_NCQ_NON_DATA ; 
 int ATA_SUPPORT_NCQ_PRIO ; 
 int ATA_SUPPORT_NCQ_STREAM ; 
 int ATA_SUPPORT_NOTIFY ; 
 int ATA_SUPPORT_OVERWRITE_EXT ; 
 int ATA_SUPPORT_POWERMGT ; 
 int ATA_SUPPORT_RCVSND_FPDMA_QUEUED ; 
 int ATA_SUPPORT_RZAT ; 
 int ATA_SUPPORT_SANITIZE ; 
 int ATA_SUPPORT_SANITIZE_ALLOWED ; 
 int ATA_SUPPORT_SECURITY ; 
 int ATA_SUPPORT_SENSE_REPORT ; 
 int ATA_SUPPORT_SMART ; 
 int ATA_SUPPORT_STANDBY ; 
 int ATA_SUPPORT_TCG ; 
 int ATA_SUPPORT_UNLOAD ; 
 int ATA_SUPPORT_WRITECACHE ; 
 int ATA_SUPPORT_WRITEREADVERIFY ; 
#define  ATA_SUPPORT_ZONE_DEV_MANAGED 129 
#define  ATA_SUPPORT_ZONE_HOST_AWARE 128 
 int ATA_SUPPORT_ZONE_MASK ; 
 scalar_t__ ata_logical_sector_offset (struct ata_params*) ; 
 int ata_logical_sector_size (struct ata_params*) ; 
 int ata_max_pmode (struct ata_params*) ; 
 scalar_t__ ata_physical_sector_size (struct ata_params*) ; 
 int ata_version (int /*<<< orphan*/ ) ; 
 scalar_t__ atasata (struct ata_params*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
atacapprint(struct ata_params *parm)
{
	const char *proto;
	u_int32_t lbasize = (u_int32_t)parm->lba_size_1 |
				((u_int32_t)parm->lba_size_2 << 16);

	u_int64_t lbasize48 = ((u_int64_t)parm->lba_size48_1) |
				((u_int64_t)parm->lba_size48_2 << 16) |
				((u_int64_t)parm->lba_size48_3 << 32) |
				((u_int64_t)parm->lba_size48_4 << 48);

	printf("\n");
	printf("protocol              ");
	proto = (parm->config == ATA_PROTO_CFA) ? "CFA" :
		(parm->config & ATA_PROTO_ATAPI) ? "ATAPI" : "ATA";
	if (ata_version(parm->version_major) == 0) {
		printf("%s", proto);
	} else if (ata_version(parm->version_major) <= 7) {
		printf("%s-%d", proto,
		    ata_version(parm->version_major));
	} else if (ata_version(parm->version_major) == 8) {
		printf("%s8-ACS", proto);
	} else {
		printf("ACS-%d %s",
		    ata_version(parm->version_major) - 7, proto);
	}
	if (parm->satacapabilities && parm->satacapabilities != 0xffff) {
		if (parm->satacapabilities & ATA_SATA_GEN3)
			printf(" SATA 3.x\n");
		else if (parm->satacapabilities & ATA_SATA_GEN2)
			printf(" SATA 2.x\n");
		else if (parm->satacapabilities & ATA_SATA_GEN1)
			printf(" SATA 1.x\n");
		else
			printf(" SATA\n");
	}
	else
		printf("\n");
	printf("device model          %.40s\n", parm->model);
	printf("firmware revision     %.8s\n", parm->revision);
	printf("serial number         %.20s\n", parm->serial);
	if (parm->enabled.extension & ATA_SUPPORT_64BITWWN) {
		printf("WWN                   %04x%04x%04x%04x\n",
		    parm->wwn[0], parm->wwn[1], parm->wwn[2], parm->wwn[3]);
	}
	printf("additional product id %.8s\n", parm->product_id);
	if (parm->enabled.extension & ATA_SUPPORT_MEDIASN) {
		printf("media serial number   %.30s\n",
		    parm->media_serial);
	}

	printf("cylinders             %d\n", parm->cylinders);
	printf("heads                 %d\n", parm->heads);
	printf("sectors/track         %d\n", parm->sectors);
	printf("sector size           logical %u, physical %lu, offset %lu\n",
	    ata_logical_sector_size(parm),
	    (unsigned long)ata_physical_sector_size(parm),
	    (unsigned long)ata_logical_sector_offset(parm));

	if (parm->config == ATA_PROTO_CFA ||
	    (parm->support.command2 & ATA_SUPPORT_CFA))
		printf("CFA supported\n");

	printf("LBA%ssupported         ",
		parm->capabilities1 & ATA_SUPPORT_LBA ? " " : " not ");
	if (lbasize)
		printf("%d sectors\n", lbasize);
	else
		printf("\n");

	printf("LBA48%ssupported       ",
		parm->support.command2 & ATA_SUPPORT_ADDRESS48 ? " " : " not ");
	if (lbasize48)
		printf("%ju sectors\n", (uintmax_t)lbasize48);
	else
		printf("\n");

	printf("PIO supported         PIO");
	switch (ata_max_pmode(parm)) {
	case ATA_PIO4:
		printf("4");
		break;
	case ATA_PIO3:
		printf("3");
		break;
	case ATA_PIO2:
		printf("2");
		break;
	case ATA_PIO1:
		printf("1");
		break;
	default:
		printf("0");
	}
	if ((parm->capabilities1 & ATA_SUPPORT_IORDY) == 0)
		printf(" w/o IORDY");
	printf("\n");

	printf("DMA%ssupported         ",
		parm->capabilities1 & ATA_SUPPORT_DMA ? " " : " not ");
	if (parm->capabilities1 & ATA_SUPPORT_DMA) {
		if (parm->mwdmamodes & 0xff) {
			printf("WDMA");
			if (parm->mwdmamodes & 0x04)
				printf("2");
			else if (parm->mwdmamodes & 0x02)
				printf("1");
			else if (parm->mwdmamodes & 0x01)
				printf("0");
			printf(" ");
		}
		if ((parm->atavalid & ATA_FLAG_88) &&
		    (parm->udmamodes & 0xff)) {
			printf("UDMA");
			if (parm->udmamodes & 0x40)
				printf("6");
			else if (parm->udmamodes & 0x20)
				printf("5");
			else if (parm->udmamodes & 0x10)
				printf("4");
			else if (parm->udmamodes & 0x08)
				printf("3");
			else if (parm->udmamodes & 0x04)
				printf("2");
			else if (parm->udmamodes & 0x02)
				printf("1");
			else if (parm->udmamodes & 0x01)
				printf("0");
			printf(" ");
		}
	}
	printf("\n");

	if (parm->media_rotation_rate == 1) {
		printf("media RPM             non-rotating\n");
	} else if (parm->media_rotation_rate >= 0x0401 &&
	    parm->media_rotation_rate <= 0xFFFE) {
		printf("media RPM             %d\n",
			parm->media_rotation_rate);
	}

	printf("Zoned-Device Commands ");
	switch (parm->support3 & ATA_SUPPORT_ZONE_MASK) {
		case ATA_SUPPORT_ZONE_DEV_MANAGED:
			printf("device managed\n");
			break;
		case ATA_SUPPORT_ZONE_HOST_AWARE:
			printf("host aware\n");
			break;
		default:
			printf("no\n");
	}

	printf("\nFeature                      "
		"Support  Enabled   Value           Vendor\n");
	printf("read ahead                     %s	%s\n",
		parm->support.command1 & ATA_SUPPORT_LOOKAHEAD ? "yes" : "no",
		parm->enabled.command1 & ATA_SUPPORT_LOOKAHEAD ? "yes" : "no");
	printf("write cache                    %s	%s\n",
		parm->support.command1 & ATA_SUPPORT_WRITECACHE ? "yes" : "no",
		parm->enabled.command1 & ATA_SUPPORT_WRITECACHE ? "yes" : "no");
	printf("flush cache                    %s	%s\n",
		parm->support.command2 & ATA_SUPPORT_FLUSHCACHE ? "yes" : "no",
		parm->enabled.command2 & ATA_SUPPORT_FLUSHCACHE ? "yes" : "no");
	printf("Native Command Queuing (NCQ)   ");
	if (atasata(parm) && (parm->satacapabilities & ATA_SUPPORT_NCQ)) {
		printf("yes		%d tags\n",
		    ATA_QUEUE_LEN(parm->queue) + 1);
		printf("NCQ Priority Information       %s\n",
		    parm->satacapabilities & ATA_SUPPORT_NCQ_PRIO ?
		    "yes" : "no");
		printf("NCQ Non-Data Command           %s\n",
		    parm->satacapabilities2 & ATA_SUPPORT_NCQ_NON_DATA ?
		    "yes" : "no");
		printf("NCQ Streaming                  %s\n",
		    parm->satacapabilities2 & ATA_SUPPORT_NCQ_STREAM ?
		    "yes" : "no");
		printf("Receive & Send FPDMA Queued    %s\n",
		    parm->satacapabilities2 & ATA_SUPPORT_RCVSND_FPDMA_QUEUED ?
		    "yes" : "no");
		printf("NCQ Autosense                  %s\n",
		    parm->satasupport & ATA_SUPPORT_NCQ_AUTOSENSE ?
		    "yes" : "no");
	} else
		printf("no\n");

	printf("SMART                          %s	%s\n",
		parm->support.command1 & ATA_SUPPORT_SMART ? "yes" : "no",
		parm->enabled.command1 & ATA_SUPPORT_SMART ? "yes" : "no");
	printf("security                       %s	%s\n",
		parm->support.command1 & ATA_SUPPORT_SECURITY ? "yes" : "no",
		parm->enabled.command1 & ATA_SUPPORT_SECURITY ? "yes" : "no");
	printf("power management               %s	%s\n",
		parm->support.command1 & ATA_SUPPORT_POWERMGT ? "yes" : "no",
		parm->enabled.command1 & ATA_SUPPORT_POWERMGT ? "yes" : "no");
	printf("microcode download             %s	%s\n",
		parm->support.command2 & ATA_SUPPORT_MICROCODE ? "yes" : "no",
		parm->enabled.command2 & ATA_SUPPORT_MICROCODE ? "yes" : "no");
	printf("advanced power management      %s	%s",
		parm->support.command2 & ATA_SUPPORT_APM ? "yes" : "no",
		parm->enabled.command2 & ATA_SUPPORT_APM ? "yes" : "no");
		if (parm->support.command2 & ATA_SUPPORT_APM) {
			printf("	%d/0x%02X\n",
			    parm->apm_value & 0xff, parm->apm_value & 0xff);
		} else
			printf("\n");
	printf("automatic acoustic management  %s	%s",
		parm->support.command2 & ATA_SUPPORT_AUTOACOUSTIC ? "yes" :"no",
		parm->enabled.command2 & ATA_SUPPORT_AUTOACOUSTIC ? "yes" :"no");
		if (parm->support.command2 & ATA_SUPPORT_AUTOACOUSTIC) {
			printf("	%d/0x%02X	%d/0x%02X\n",
			    ATA_ACOUSTIC_CURRENT(parm->acoustic),
			    ATA_ACOUSTIC_CURRENT(parm->acoustic),
			    ATA_ACOUSTIC_VENDOR(parm->acoustic),
			    ATA_ACOUSTIC_VENDOR(parm->acoustic));
		} else
			printf("\n");
	printf("media status notification      %s	%s\n",
		parm->support.command2 & ATA_SUPPORT_NOTIFY ? "yes" : "no",
		parm->enabled.command2 & ATA_SUPPORT_NOTIFY ? "yes" : "no");
	printf("power-up in Standby            %s	%s\n",
		parm->support.command2 & ATA_SUPPORT_STANDBY ? "yes" : "no",
		parm->enabled.command2 & ATA_SUPPORT_STANDBY ? "yes" : "no");
	printf("write-read-verify              %s	%s",
		parm->support2 & ATA_SUPPORT_WRITEREADVERIFY ? "yes" : "no",
		parm->enabled2 & ATA_SUPPORT_WRITEREADVERIFY ? "yes" : "no");
		if (parm->support2 & ATA_SUPPORT_WRITEREADVERIFY) {
			printf("	%d/0x%x\n",
			    parm->wrv_mode, parm->wrv_mode);
		} else
			printf("\n");
	printf("unload                         %s	%s\n",
		parm->support.extension & ATA_SUPPORT_UNLOAD ? "yes" : "no",
		parm->enabled.extension & ATA_SUPPORT_UNLOAD ? "yes" : "no");
	printf("general purpose logging        %s	%s\n",
		parm->support.extension & ATA_SUPPORT_GENLOG ? "yes" : "no",
		parm->enabled.extension & ATA_SUPPORT_GENLOG ? "yes" : "no");
	printf("free-fall                      %s	%s\n",
		parm->support2 & ATA_SUPPORT_FREEFALL ? "yes" : "no",
		parm->enabled2 & ATA_SUPPORT_FREEFALL ? "yes" : "no");
	printf("sense data reporting           %s	%s\n",
		parm->support2 & ATA_SUPPORT_SENSE_REPORT ? "yes" : "no",
		parm->enabled2 & ATA_SUPPORT_SENSE_REPORT ? "yes" : "no");
	printf("extended power conditions      %s	%s\n",
		parm->support2 & ATA_SUPPORT_EPC ? "yes" : "no",
		parm->enabled2 & ATA_SUPPORT_EPC ? "yes" : "no");
	printf("device statistics notification %s	%s\n",
		parm->support2 & ATA_SUPPORT_DSN ? "yes" : "no",
		parm->enabled2 & ATA_SUPPORT_DSN ? "yes" : "no");
	printf("Data Set Management (DSM/TRIM) ");
	if (parm->support_dsm & ATA_SUPPORT_DSM_TRIM) {
		printf("yes\n");
		printf("DSM - max 512byte blocks       ");
		if (parm->max_dsm_blocks == 0x00)
			printf("yes              not specified\n");
		else
			printf("yes              %d\n",
				parm->max_dsm_blocks);

		printf("DSM - deterministic read       ");
		if (parm->support3 & ATA_SUPPORT_DRAT) {
			if (parm->support3 & ATA_SUPPORT_RZAT)
				printf("yes              zeroed\n");
			else
				printf("yes              any value\n");
		} else {
			printf("no\n");
		}
	} else {
		printf("no\n");
	}
	printf("Trusted Computing              %s\n",
	    ((parm->tcg & 0xc000) == 0x4000) && (parm->tcg & ATA_SUPPORT_TCG) ?
	    "yes" : "no");
	printf("encrypts all user data         %s\n",
		parm->support3 & ATA_ENCRYPTS_ALL_USER_DATA ? "yes" : "no");
	printf("Sanitize                       ");
	if (parm->multi & ATA_SUPPORT_SANITIZE) {
		printf("yes\t\t%s%s%s\n",
		    parm->multi & ATA_SUPPORT_BLOCK_ERASE_EXT ? "block, " : "",
		    parm->multi & ATA_SUPPORT_OVERWRITE_EXT ? "overwrite, " : "",
		    parm->multi & ATA_SUPPORT_CRYPTO_SCRAMBLE_EXT ? "crypto" : "");
		printf("Sanitize - commands allowed    %s\n",
		    parm->multi & ATA_SUPPORT_SANITIZE_ALLOWED ? "yes" : "no");
		printf("Sanitize - antifreeze lock     %s\n",
		    parm->multi & ATA_SUPPORT_ANTIFREEZE_LOCK_EXT ? "yes" : "no");
	} else {
		printf("no\n");
	}
}