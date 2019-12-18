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
struct ooo_opaque {int dummy; } ;
struct ecore_ooo_history {size_t head_idx; size_t num_of_cqes; struct ooo_opaque* p_cqes; } ;
struct ecore_ooo_info {struct ecore_ooo_history ooo_history; } ;

/* Variables and functions */

void ecore_ooo_save_history_entry(struct ecore_ooo_info *p_ooo_info,
				  struct ooo_opaque *p_cqe)
{
	struct ecore_ooo_history *p_history = &p_ooo_info->ooo_history;

	if (p_history->head_idx == p_history->num_of_cqes)
			p_history->head_idx = 0;
	p_history->p_cqes[p_history->head_idx] = *p_cqe;
	p_history->head_idx++;
}