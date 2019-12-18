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
struct icp_qat_uof_strtable {scalar_t__ strings; int /*<<< orphan*/  table_len; } ;
struct icp_qat_uof_objhdr {int dummy; } ;
struct icp_qat_uof_chunkhdr {scalar_t__ offset; } ;
struct icp_qat_uclo_objhdr {scalar_t__ file_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct icp_qat_uof_chunkhdr* qat_uclo_find_chunk (struct icp_qat_uof_objhdr*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct icp_qat_uof_strtable *
qat_uclo_map_str_table(struct icp_qat_uclo_objhdr *obj_hdr,
		       char *tab_name, struct icp_qat_uof_strtable *str_table)
{
	struct icp_qat_uof_chunkhdr *chunk_hdr;

	chunk_hdr = qat_uclo_find_chunk((struct icp_qat_uof_objhdr *)
					obj_hdr->file_buff, tab_name, NULL);
	if (chunk_hdr) {
		int hdr_size;

		memcpy(&str_table->table_len, obj_hdr->file_buff +
		       chunk_hdr->offset, sizeof(str_table->table_len));
		hdr_size = (char *)&str_table->strings - (char *)str_table;
		str_table->strings = (uintptr_t)obj_hdr->file_buff +
					chunk_hdr->offset + hdr_size;
		return str_table;
	}
	return NULL;
}