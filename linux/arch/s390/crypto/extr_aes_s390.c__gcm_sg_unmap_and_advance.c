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
struct gcm_sg_walk {unsigned int walk_bytes_remain; int /*<<< orphan*/ * walk_ptr; int /*<<< orphan*/  walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  scatterwalk_advance (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _gcm_sg_unmap_and_advance(struct gcm_sg_walk *gw,
					     unsigned int nbytes)
{
	gw->walk_bytes_remain -= nbytes;
	scatterwalk_unmap(&gw->walk);
	scatterwalk_advance(&gw->walk, nbytes);
	scatterwalk_done(&gw->walk, 0, gw->walk_bytes_remain);
	gw->walk_ptr = NULL;
}