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
typedef  int /*<<< orphan*/  u16 ;
struct scatterlist {int dummy; } ;
struct dpaa2_sg_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpaa2_sg_set_final (struct dpaa2_sg_entry*,int) ; 
 struct dpaa2_sg_entry* sg_to_qm_sg (struct scatterlist*,int,struct dpaa2_sg_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sg_to_qm_sg_last(struct scatterlist *sg, int len,
				    struct dpaa2_sg_entry *qm_sg_ptr,
				    u16 offset)
{
	qm_sg_ptr = sg_to_qm_sg(sg, len, qm_sg_ptr, offset);
	dpaa2_sg_set_final(qm_sg_ptr, true);
}