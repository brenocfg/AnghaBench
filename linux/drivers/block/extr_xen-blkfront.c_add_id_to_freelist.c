#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct blkfront_ring_info {unsigned long shadow_free; TYPE_4__* shadow; } ;
struct TYPE_5__ {unsigned long id; } ;
struct TYPE_6__ {TYPE_1__ rw; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/ * request; TYPE_3__ req; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int add_id_to_freelist(struct blkfront_ring_info *rinfo,
			      unsigned long id)
{
	if (rinfo->shadow[id].req.u.rw.id != id)
		return -EINVAL;
	if (rinfo->shadow[id].request == NULL)
		return -EINVAL;
	rinfo->shadow[id].req.u.rw.id  = rinfo->shadow_free;
	rinfo->shadow[id].request = NULL;
	rinfo->shadow_free = id;
	return 0;
}