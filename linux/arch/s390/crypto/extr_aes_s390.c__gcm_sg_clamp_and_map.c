#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sg; } ;
struct gcm_sg_walk {unsigned int walk_bytes; TYPE_1__ walk; int /*<<< orphan*/  walk_ptr; int /*<<< orphan*/  walk_bytes_remain; } ;

/* Variables and functions */
 void* scatterwalk_clamp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scatterwalk_map (TYPE_1__*) ; 
 int /*<<< orphan*/  scatterwalk_start (TYPE_1__*,struct scatterlist*) ; 
 struct scatterlist* sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int _gcm_sg_clamp_and_map(struct gcm_sg_walk *gw)
{
	struct scatterlist *nextsg;

	gw->walk_bytes = scatterwalk_clamp(&gw->walk, gw->walk_bytes_remain);
	while (!gw->walk_bytes) {
		nextsg = sg_next(gw->walk.sg);
		if (!nextsg)
			return 0;
		scatterwalk_start(&gw->walk, nextsg);
		gw->walk_bytes = scatterwalk_clamp(&gw->walk,
						   gw->walk_bytes_remain);
	}
	gw->walk_ptr = scatterwalk_map(&gw->walk);
	return gw->walk_bytes;
}