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
struct torus {scalar_t__*** sw; } ;
struct t_switch {size_t i; size_t j; size_t k; } ;

/* Variables and functions */
 int next_hop_idx (struct torus*,int,struct t_switch*,struct t_switch*,unsigned int*) ; 
 int next_hop_path (struct torus*,int,struct t_switch*,struct t_switch*,unsigned int*) ; 

__attribute__((used)) static
bool next_hop_y(struct torus *t,
		struct t_switch *ssw, struct t_switch *dsw, unsigned *pt_grp)
{
	if (t->sw[ssw->i][dsw->j][ssw->k])
		/*
		 * The next turning switch on this path is available,
		 * so head towards it by the shortest available path.
		 */
		return next_hop_path(t, 1, ssw, dsw, pt_grp);
	else
		/*
		 * The next turning switch on this path is not
		 * available, so head towards it in the shortest
		 * path direction.
		 */
		return next_hop_idx(t, 1, ssw, dsw, pt_grp);
}