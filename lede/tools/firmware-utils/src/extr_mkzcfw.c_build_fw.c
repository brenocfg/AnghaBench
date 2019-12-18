#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct fw_tail {void* crc; void* hw_id; } ;
struct fw_header {void* length; void* magic; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_id; } ;
struct TYPE_5__ {int file_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 void* HOST_TO_BE32 (int /*<<< orphan*/ ) ; 
 void* HOST_TO_LE32 (int) ; 
 int MAGIC_FIRMWARE ; 
 int MAGIC_KERNEL ; 
 int MAGIC_ROOTFS ; 
 TYPE_4__* board ; 
 int /*<<< orphan*/  cyg_crc32 (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ kernel_info ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int read_to_buf (TYPE_1__*,char*) ; 
 TYPE_1__ rootfs_info ; 
 int write_fw (char*,int) ; 

__attribute__((used)) static int build_fw(void)
{
	int buflen;
	char *buf;
	char *p;
	int ret = EXIT_FAILURE;
	int writelen = 0;
	uint32_t crc;
	struct fw_header *hdr;
	struct fw_tail *tail;

	buflen = 3 * sizeof(struct fw_header) +
		 kernel_info.file_size + rootfs_info.file_size +
		 3 * sizeof(struct fw_tail);

	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto out;
	}

	p = buf;
	memset(p, 0, buflen);

	/* fill firmware header */
	hdr = (struct fw_header *) p;
	hdr->magic = HOST_TO_LE32(MAGIC_FIRMWARE);
	hdr->length = HOST_TO_LE32(buflen - sizeof(struct fw_header));
	p += sizeof(struct fw_header);

	/* fill kernel block header */
	hdr = (struct fw_header *) p;
	hdr->magic = HOST_TO_LE32(MAGIC_KERNEL);
	hdr->length = HOST_TO_LE32(kernel_info.file_size +
				   sizeof(struct fw_tail));
	p += sizeof(struct fw_header);

	/* read kernel data */
	ret = read_to_buf(&kernel_info, p);
	if (ret)
		goto out_free_buf;

	/* fill firmware tail */
	tail = (struct fw_tail *) (p + kernel_info.file_size);
	tail->hw_id = HOST_TO_BE32(board->hw_id);
	tail->crc = HOST_TO_BE32(cyg_crc32(p, kernel_info.file_size +
				 	   sizeof(struct fw_tail) - 4));

	p += kernel_info.file_size + sizeof(struct fw_tail);

	/* fill rootfs block header */
	hdr = (struct fw_header *) p;
	hdr->magic = HOST_TO_LE32(MAGIC_ROOTFS);
	hdr->length = HOST_TO_LE32(rootfs_info.file_size +
				   sizeof(struct fw_tail));
	p += sizeof(struct fw_header);

	/* read rootfs data */
	ret = read_to_buf(&rootfs_info, p);
	if (ret)
		goto out_free_buf;

	/* fill firmware tail */
	tail = (struct fw_tail *) (p + rootfs_info.file_size);
	tail->hw_id = HOST_TO_BE32(board->hw_id);
	tail->crc = HOST_TO_BE32(cyg_crc32(p, rootfs_info.file_size +
				 	   sizeof(struct fw_tail) - 4));

	p += rootfs_info.file_size + sizeof(struct fw_tail);

	/* fill firmware tail */
	tail = (struct fw_tail *) p;
	tail->hw_id = HOST_TO_BE32(board->hw_id);
	tail->crc = HOST_TO_BE32(cyg_crc32(buf + sizeof(struct fw_header),
				 buflen - sizeof(struct fw_header) - 4));

	ret = write_fw(buf, buflen);
	if (ret)
		goto out_free_buf;

	ret = EXIT_SUCCESS;

 out_free_buf:
	free(buf);
 out:
	return ret;
}