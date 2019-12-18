#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sglist {int sg_nseg; TYPE_1__* sg_segs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ss_len; } ;

/* Variables and functions */
 scalar_t__ howmany (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ccr_count_sgl(struct sglist *sg, int maxsegsize)
{
	int i, nsegs;

	nsegs = 0;
	for (i = 0; i < sg->sg_nseg; i++)
		nsegs += howmany(sg->sg_segs[i].ss_len, maxsegsize);
	return (nsegs);
}