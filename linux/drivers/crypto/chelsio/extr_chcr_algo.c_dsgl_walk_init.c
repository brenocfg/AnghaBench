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
struct phys_sge_pairs {int dummy; } ;
struct dsgl_walk {struct phys_sge_pairs* to; scalar_t__ nents; struct cpl_rx_phys_dsgl* dsgl; } ;
struct cpl_rx_phys_dsgl {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void dsgl_walk_init(struct dsgl_walk *walk,
				   struct cpl_rx_phys_dsgl *dsgl)
{
	walk->dsgl = dsgl;
	walk->nents = 0;
	walk->to = (struct phys_sge_pairs *)(dsgl + 1);
}