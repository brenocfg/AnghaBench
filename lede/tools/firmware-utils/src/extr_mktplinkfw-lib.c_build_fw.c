#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fw_max_len; } ;
struct TYPE_5__ {int file_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ add_jffs2_eof ; 
 scalar_t__ combined ; 
 int /*<<< orphan*/  fill_header (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ kernel_info ; 
 size_t kernel_len ; 
 TYPE_3__* layout ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ofname ; 
 int pad_jffs2 (char*,int,int) ; 
 int read_to_buf (TYPE_1__*,char*) ; 
 TYPE_1__ rootfs_info ; 
 int rootfs_ofs ; 
 int /*<<< orphan*/  strip_padding ; 
 int write_fw (int /*<<< orphan*/ ,char*,int) ; 

int build_fw(size_t header_size)
{
	int buflen;
	char *buf;
	char *p;
	int ret = EXIT_FAILURE;
	int writelen = 0;

	writelen = header_size + kernel_len;

	if (combined)
		buflen = writelen;
	else
		buflen = layout->fw_max_len;

	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto out;
	}

	memset(buf, 0xff, buflen);
	p = buf + header_size;
	ret = read_to_buf(&kernel_info, p);
	if (ret)
		goto out_free_buf;

	if (!combined) {
		p = buf + rootfs_ofs;

		ret = read_to_buf(&rootfs_info, p);
		if (ret)
			goto out_free_buf;

		writelen = rootfs_ofs + rootfs_info.file_size;

		if (add_jffs2_eof)
			writelen = pad_jffs2(buf, writelen, layout->fw_max_len);
	}

	if (!strip_padding)
		writelen = buflen;

	fill_header(buf, writelen);
	ret = write_fw(ofname, buf, writelen);
	if (ret)
		goto out_free_buf;

	ret = EXIT_SUCCESS;

out_free_buf:
	free(buf);
out:
	return ret;
}