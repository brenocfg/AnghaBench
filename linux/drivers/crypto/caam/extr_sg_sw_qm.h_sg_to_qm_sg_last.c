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
struct qm_sg_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qm_sg_entry_get_len (struct qm_sg_entry*) ; 
 int /*<<< orphan*/  qm_sg_entry_set_f (struct qm_sg_entry*,int /*<<< orphan*/ ) ; 
 struct qm_sg_entry* sg_to_qm_sg (struct scatterlist*,int,struct qm_sg_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sg_to_qm_sg_last(struct scatterlist *sg, int len,
				    struct qm_sg_entry *qm_sg_ptr, u16 offset)
{
	qm_sg_ptr = sg_to_qm_sg(sg, len, qm_sg_ptr, offset);
	qm_sg_entry_set_f(qm_sg_ptr, qm_sg_entry_get_len(qm_sg_ptr));
}