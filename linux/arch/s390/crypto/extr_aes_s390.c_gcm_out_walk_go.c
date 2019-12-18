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
struct gcm_sg_walk {scalar_t__ walk_bytes_remain; int nbytes; unsigned int walk_bytes; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * walk_ptr; int /*<<< orphan*/  walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  _gcm_sg_clamp_and_map (struct gcm_sg_walk*) ; 
 int /*<<< orphan*/  scatterwalk_unmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gcm_out_walk_go(struct gcm_sg_walk *gw, unsigned int minbytesneeded)
{
	if (gw->walk_bytes_remain == 0) {
		gw->ptr = NULL;
		gw->nbytes = 0;
		goto out;
	}

	if (!_gcm_sg_clamp_and_map(gw)) {
		gw->ptr = NULL;
		gw->nbytes = 0;
		goto out;
	}

	if (gw->walk_bytes >= minbytesneeded) {
		gw->ptr = gw->walk_ptr;
		gw->nbytes = gw->walk_bytes;
		goto out;
	}

	scatterwalk_unmap(&gw->walk);
	gw->walk_ptr = NULL;

	gw->ptr = gw->buf;
	gw->nbytes = sizeof(gw->buf);

out:
	return gw->nbytes;
}