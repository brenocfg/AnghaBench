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
typedef  scalar_t__ u32 ;
struct cudbg_hdr {scalar_t__ hdr_len; } ;
struct cudbg_entity_hdr {int dummy; } ;

/* Variables and functions */
 int CUDBG_STATUS_SMALL_BUFF ; 

int get_entity_hdr(void *outbuf, int i, u32 size,
		   struct cudbg_entity_hdr **entity_hdr)
{
	int rc = 0;
	struct cudbg_hdr *cudbg_hdr = (struct cudbg_hdr *)outbuf;

	if (cudbg_hdr->hdr_len + (sizeof(struct cudbg_entity_hdr)*i) > size)
		return CUDBG_STATUS_SMALL_BUFF;

	*entity_hdr = (struct cudbg_entity_hdr *)
		      ((char *)outbuf+cudbg_hdr->hdr_len +
		       (sizeof(struct cudbg_entity_hdr)*(i-1)));
	return rc;
}