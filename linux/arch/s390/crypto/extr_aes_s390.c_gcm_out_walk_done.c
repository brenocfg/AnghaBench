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
struct gcm_sg_walk {int /*<<< orphan*/ * buf; int /*<<< orphan*/  walk_ptr; int /*<<< orphan*/  walk_bytes; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _gcm_sg_clamp_and_map (struct gcm_sg_walk*) ; 
 int /*<<< orphan*/  _gcm_sg_unmap_and_advance (struct gcm_sg_walk*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int min (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int gcm_out_walk_done(struct gcm_sg_walk *gw, unsigned int bytesdone)
{
	int i, n;

	if (gw->ptr == NULL)
		return 0;

	if (gw->ptr == gw->buf) {
		for (i = 0; i < bytesdone; i += n) {
			if (!_gcm_sg_clamp_and_map(gw))
				return i;
			n = min(gw->walk_bytes, bytesdone - i);
			memcpy(gw->walk_ptr, gw->buf + i, n);
			_gcm_sg_unmap_and_advance(gw, n);
		}
	} else
		_gcm_sg_unmap_and_advance(gw, bytesdone);

	return bytesdone;
}