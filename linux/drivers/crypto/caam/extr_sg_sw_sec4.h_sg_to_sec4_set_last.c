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
struct sec4_sg_entry {int /*<<< orphan*/  len; } ;
struct dpaa2_sg_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC4_SG_LEN_FIN ; 
 scalar_t__ caam_dpaa2 ; 
 int /*<<< orphan*/  cpu_to_caam32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_set_final (struct dpaa2_sg_entry*,int) ; 

__attribute__((used)) static inline void sg_to_sec4_set_last(struct sec4_sg_entry *sec4_sg_ptr)
{
	if (caam_dpaa2)
		dpaa2_sg_set_final((struct dpaa2_sg_entry *)sec4_sg_ptr, true);
	else
		sec4_sg_ptr->len |= cpu_to_caam32(SEC4_SG_LEN_FIN);
}