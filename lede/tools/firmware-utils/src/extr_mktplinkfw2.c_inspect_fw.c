#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct fw_header {int kernel_la; int kernel_ep; int version; int boot_len; int unk2; int unk3; int unk4; int unk5; char* fw_version; int hw_id; int hw_rev; int hw_ver_add; int ver_hi; int ver_mid; int ver_lo; int sver_hi; int sver_lo; int kernel_ofs; int kernel_len; int rootfs_ofs; int rootfs_len; int boot_ofs; int fw_length; int /*<<< orphan*/ * md5sum2; int /*<<< orphan*/ * md5sum1; } ;
struct board_info {int flags; } ;
typedef  int /*<<< orphan*/  md5sum ;
struct TYPE_3__ {int file_size; char* file_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int EXIT_FAILURE ; 
 int FLAG_LE_KERNEL_LA_EP ; 
 int MD5SUM_LEN ; 
 int bswap_32 (int) ; 
 struct board_info custom_board ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ extract ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_md5 (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inspect_fw_phex (char*,int) ; 
 int /*<<< orphan*/  inspect_fw_phexdec (char*,int) ; 
 int /*<<< orphan*/  inspect_fw_pmd5sum (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  inspect_fw_pstr (char*,char*) ; 
 TYPE_1__ inspect_info ; 
 char* malloc (int) ; 
 int /*<<< orphan*/ * md5salt_boot ; 
 int /*<<< orphan*/ * md5salt_normal ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ntohl (int) ; 
 int ntohs (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_to_buf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static int inspect_fw(void)
{
	char *buf;
	struct fw_header *hdr;
	uint8_t md5sum[MD5SUM_LEN];
	struct board_info *board;
	int ret = EXIT_FAILURE;

	buf = malloc(inspect_info.file_size);
	if (!buf) {
		ERR("no memory for buffer!\n");
		goto out;
	}

	ret = read_to_buf(&inspect_info, buf);
	if (ret)
		goto out_free_buf;
	hdr = (struct fw_header *)buf;

	board = &custom_board;

	if (board->flags & FLAG_LE_KERNEL_LA_EP) {
		hdr->kernel_la = bswap_32(hdr->kernel_la);
		hdr->kernel_ep = bswap_32(hdr->kernel_ep);
	}

	inspect_fw_pstr("File name", inspect_info.file_name);
	inspect_fw_phexdec("File size", inspect_info.file_size);

	switch(bswap_32(ntohl(hdr->version))) {
	case 2:
	case 3:
		break;
	default:
		ERR("file does not seem to have V2/V3 header!\n");
		goto out_free_buf;
	}

	inspect_fw_phexdec("Version 2 Header size", sizeof(struct fw_header));

	memcpy(md5sum, hdr->md5sum1, sizeof(md5sum));
	if (ntohl(hdr->boot_len) == 0)
		memcpy(hdr->md5sum1, md5salt_normal, sizeof(md5sum));
	else
		memcpy(hdr->md5sum1, md5salt_boot, sizeof(md5sum));
	get_md5(buf, inspect_info.file_size, hdr->md5sum1);

	if (memcmp(md5sum, hdr->md5sum1, sizeof(md5sum))) {
		inspect_fw_pmd5sum("Header MD5Sum1", md5sum, "(*ERROR*)");
		inspect_fw_pmd5sum("          --> expected", hdr->md5sum1, "");
	} else {
		inspect_fw_pmd5sum("Header MD5Sum1", md5sum, "(ok)");
	}
	if (ntohl(hdr->unk2) != 0)
		inspect_fw_phexdec("Unknown value 2", hdr->unk2);
	inspect_fw_pmd5sum("Header MD5Sum2", hdr->md5sum2,
	                   "(purpose yet unknown, unchecked here)");

	if (ntohl(hdr->unk3) != 0xffffffff)
		inspect_fw_phexdec("Unknown value 3", hdr->unk3);

	if (ntohs(hdr->unk4) != 0x55aa)
		inspect_fw_phexdec("Unknown value 4", hdr->unk4);

	if (hdr->unk5 != 0xa5)
		inspect_fw_phexdec("Unknown value 5", hdr->unk5);

	printf("\n");

	inspect_fw_pstr("Firmware version", hdr->fw_version);
	inspect_fw_phex("Hardware ID", ntohl(hdr->hw_id));
	inspect_fw_phex("Hardware Revision",
			ntohl(hdr->hw_rev));
	inspect_fw_phex("Additional HW Version",
			ntohl(hdr->hw_ver_add));

	printf("%-23s: %d.%d.%d-%d.%d\n", "Software version",
	       hdr->ver_hi, hdr->ver_mid, hdr->ver_lo,
	       hdr->sver_hi, hdr->sver_lo);

	printf("\n");

	inspect_fw_phexdec("Kernel data offset",
	                   ntohl(hdr->kernel_ofs));
	inspect_fw_phexdec("Kernel data length",
	                   ntohl(hdr->kernel_len));
	inspect_fw_phex("Kernel load address",
			ntohl(hdr->kernel_la));
	inspect_fw_phex("Kernel entry point",
			ntohl(hdr->kernel_ep));
	inspect_fw_phexdec("Rootfs data offset",
			   ntohl(hdr->rootfs_ofs));
	inspect_fw_phexdec("Rootfs data length",
	                   ntohl(hdr->rootfs_len));
	inspect_fw_phexdec("Boot loader data offset",
	                   ntohl(hdr->boot_ofs));
	inspect_fw_phexdec("Boot loader data length",
	                   ntohl(hdr->boot_len));
	inspect_fw_phexdec("Total firmware length",
	                   ntohl(hdr->fw_length));

	if (extract) {
		FILE *fp;
		char *filename;

		printf("\n");

		filename = malloc(strlen(inspect_info.file_name) + 8);
		sprintf(filename, "%s-kernel", inspect_info.file_name);
		printf("Extracting kernel to \"%s\"...\n", filename);
		fp = fopen(filename, "w");
		if (fp)	{
			if (!fwrite(buf + ntohl(hdr->kernel_ofs),
			            ntohl(hdr->kernel_len), 1, fp)) {
				ERR("error in fwrite(): %s", strerror(errno));
			}
			fclose(fp);
		} else {
			ERR("error in fopen(): %s", strerror(errno));
		}
		free(filename);

		filename = malloc(strlen(inspect_info.file_name) + 8);
		sprintf(filename, "%s-rootfs", inspect_info.file_name);
		printf("Extracting rootfs to \"%s\"...\n", filename);
		fp = fopen(filename, "w");
		if (fp)	{
			if (!fwrite(buf + ntohl(hdr->rootfs_ofs),
			            ntohl(hdr->rootfs_len), 1, fp)) {
				ERR("error in fwrite(): %s", strerror(errno));
			}
			fclose(fp);
		} else {
			ERR("error in fopen(): %s", strerror(errno));
		}
		free(filename);
	}

 out_free_buf:
	free(buf);
 out:
	return ret;
}