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
struct torus {int dummy; } ;
struct t_switch {int dummy; } ;

/* Variables and functions */
 int next_hop_path (struct torus*,int,struct t_switch*,struct t_switch*,unsigned int*) ; 

__attribute__((used)) static
bool next_hop_z(struct torus *t,
		struct t_switch *ssw, struct t_switch *dsw, unsigned *pt_grp)
{
	return next_hop_path(t, 2, ssw, dsw, pt_grp);
}