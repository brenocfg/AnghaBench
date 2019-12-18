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
typedef  unsigned long uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct papr_scm_priv {scalar_t__ metadata_size; int /*<<< orphan*/  drc_index; } ;
struct nd_cmd_get_config_data_hdr {scalar_t__ in_offset; scalar_t__ in_length; int /*<<< orphan*/  out_buf; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ H_PARAMETER ; 
 int /*<<< orphan*/  H_SCM_READ_METADATA ; 
 int PLPAR_HCALL_BUFSIZE ; 
 int /*<<< orphan*/  be16_to_cpu (unsigned long) ; 
 int /*<<< orphan*/  be32_to_cpu (unsigned long) ; 
 int /*<<< orphan*/  be64_to_cpu (unsigned long) ; 
 scalar_t__ plpar_hcall (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static int papr_scm_meta_get(struct papr_scm_priv *p,
			     struct nd_cmd_get_config_data_hdr *hdr)
{
	unsigned long data[PLPAR_HCALL_BUFSIZE];
	unsigned long offset, data_offset;
	int len, read;
	int64_t ret;

	if ((hdr->in_offset + hdr->in_length) >= p->metadata_size)
		return -EINVAL;

	for (len = hdr->in_length; len; len -= read) {

		data_offset = hdr->in_length - len;
		offset = hdr->in_offset + data_offset;

		if (len >= 8)
			read = 8;
		else if (len >= 4)
			read = 4;
		else if (len >= 2)
			read = 2;
		else
			read = 1;

		ret = plpar_hcall(H_SCM_READ_METADATA, data, p->drc_index,
				  offset, read);

		if (ret == H_PARAMETER) /* bad DRC index */
			return -ENODEV;
		if (ret)
			return -EINVAL; /* other invalid parameter */

		switch (read) {
		case 8:
			*(uint64_t *)(hdr->out_buf + data_offset) = be64_to_cpu(data[0]);
			break;
		case 4:
			*(uint32_t *)(hdr->out_buf + data_offset) = be32_to_cpu(data[0] & 0xffffffff);
			break;

		case 2:
			*(uint16_t *)(hdr->out_buf + data_offset) = be16_to_cpu(data[0] & 0xffff);
			break;

		case 1:
			*(uint8_t *)(hdr->out_buf + data_offset) = (data[0] & 0xff);
			break;
		}
	}
	return 0;
}