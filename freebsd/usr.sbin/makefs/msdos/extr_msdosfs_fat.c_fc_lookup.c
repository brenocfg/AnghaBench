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
typedef  scalar_t__ u_long ;
struct fatcache {scalar_t__ fc_frcn; scalar_t__ fc_fsrcn; } ;
struct denode {struct fatcache* de_fc; } ;

/* Variables and functions */
 scalar_t__ FCE_EMPTY ; 
 int FC_SIZE ; 

__attribute__((used)) static void
fc_lookup(struct denode *dep, u_long findcn, u_long *frcnp, u_long *fsrcnp)
{
	int i;
	u_long cn;
	struct fatcache *closest = NULL;

	for (i = 0; i < FC_SIZE; i++) {
		cn = dep->de_fc[i].fc_frcn;
		if (cn != FCE_EMPTY && cn <= findcn) {
			if (closest == NULL || cn > closest->fc_frcn)
				closest = &dep->de_fc[i];
		}
	}
	if (closest) {
		*frcnp = closest->fc_frcn;
		*fsrcnp = closest->fc_fsrcn;
	}
}