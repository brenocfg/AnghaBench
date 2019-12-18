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
struct snapshot {int u; int v; int perpage; int pages; scalar_t__ ptr; } ;
struct devstat {int dummy; } ;

/* Variables and functions */
 int pagesize ; 

struct devstat *
geom_stats_snapshot_next(void *arg)
{
	struct devstat *gsp;
	struct snapshot *sp;

	sp = arg;
	gsp = (struct devstat *)
	    (sp->ptr + sp->u * pagesize + sp->v * sizeof *gsp);
	if (++sp->v >= sp->perpage) {
		if (++sp->u >= sp->pages)
			return (NULL);
		else
			sp->v = 0;
	}
	return (gsp);
}