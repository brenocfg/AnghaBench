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
typedef  int u8 ;
struct scatterlist {int dummy; } ;
struct ccp_dm_workarea {int* address; } ;

/* Variables and functions */
 int ccp_set_dm_area (struct ccp_dm_workarea*,unsigned int,struct scatterlist*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ccp_reverse_set_dm_area(struct ccp_dm_workarea *wa,
				   unsigned int wa_offset,
				   struct scatterlist *sg,
				   unsigned int sg_offset,
				   unsigned int len)
{
	u8 *p, *q;
	int	rc;

	rc = ccp_set_dm_area(wa, wa_offset, sg, sg_offset, len);
	if (rc)
		return rc;

	p = wa->address + wa_offset;
	q = p + len - 1;
	while (p < q) {
		*p = *p ^ *q;
		*q = *p ^ *q;
		*p = *p ^ *q;
		p++;
		q--;
	}
	return 0;
}