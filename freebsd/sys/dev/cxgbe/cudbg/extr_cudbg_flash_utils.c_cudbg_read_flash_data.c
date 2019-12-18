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
typedef  int u32 ;
struct cudbg_hdr {int dummy; } ;
struct cudbg_flash_hdr {int dummy; } ;
struct cudbg_entity_hdr {int dummy; } ;

/* Variables and functions */
 int CUDBG_MAX_ENTITY ; 
 int cudbg_read_flash (void*,void*,int,int) ; 

int cudbg_read_flash_data(void *handle, void *buf, u32 buf_size)
{
	int rc;
	u32 total_hdr_size, data_header_size;
	void *payload = NULL;
	u32 payload_size = 0;

	data_header_size = CUDBG_MAX_ENTITY * sizeof(struct cudbg_entity_hdr) +
		sizeof(struct cudbg_hdr);
	total_hdr_size = data_header_size + sizeof(struct cudbg_flash_hdr);

	/* Copy flash header to buffer */
	rc = cudbg_read_flash(handle, buf, total_hdr_size, 0);
	if (rc != 0)
		goto out;
	payload = (char *)buf + total_hdr_size;
	payload_size  = buf_size - total_hdr_size;

	/* Reading flash data to buf */
	rc = cudbg_read_flash(handle, payload, payload_size, 1);
	if (rc != 0)
		goto out;

out:
	return rc;
}