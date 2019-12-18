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
struct ccp_sg_workarea {scalar_t__ bytes_left; scalar_t__ sg_used; TYPE_1__* sg; } ;
struct ccp_dm_workarea {unsigned int length; int /*<<< orphan*/  address; } ;
struct ccp_data {struct ccp_dm_workarea dm_wa; struct ccp_sg_workarea sg_wa; } ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccp_update_sg_workarea (struct ccp_sg_workarea*,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min (scalar_t__,unsigned int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static unsigned int ccp_queue_buf(struct ccp_data *data, unsigned int from)
{
	struct ccp_sg_workarea *sg_wa = &data->sg_wa;
	struct ccp_dm_workarea *dm_wa = &data->dm_wa;
	unsigned int buf_count, nbytes;

	/* Clear the buffer if setting it */
	if (!from)
		memset(dm_wa->address, 0, dm_wa->length);

	if (!sg_wa->sg)
		return 0;

	/* Perform the copy operation
	 *   nbytes will always be <= UINT_MAX because dm_wa->length is
	 *   an unsigned int
	 */
	nbytes = min_t(u64, sg_wa->bytes_left, dm_wa->length);
	scatterwalk_map_and_copy(dm_wa->address, sg_wa->sg, sg_wa->sg_used,
				 nbytes, from);

	/* Update the structures and generate the count */
	buf_count = 0;
	while (sg_wa->bytes_left && (buf_count < dm_wa->length)) {
		nbytes = min(sg_wa->sg->length - sg_wa->sg_used,
			     dm_wa->length - buf_count);
		nbytes = min_t(u64, sg_wa->bytes_left, nbytes);

		buf_count += nbytes;
		ccp_update_sg_workarea(sg_wa, nbytes);
	}

	return buf_count;
}