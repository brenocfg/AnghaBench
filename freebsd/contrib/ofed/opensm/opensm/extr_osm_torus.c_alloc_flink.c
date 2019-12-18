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
struct link {int dummy; } ;
struct fabric {size_t link_cnt; size_t link_cnt_max; struct link** link; TYPE_1__* osm; } ;
struct TYPE_2__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 struct link* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct link**,int /*<<< orphan*/ ,int) ; 
 void* realloc (struct link**,unsigned int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct link *alloc_flink(struct fabric *f)
{
	unsigned cnt_max;
	struct link *l = NULL;
	void *ptr;

	if (f->link_cnt >= f->link_cnt_max) {

		cnt_max = 16 + 5 * f->link_cnt_max / 4;
		ptr = realloc(f->link, cnt_max * sizeof(*f->link));
		if (!ptr) {
			OSM_LOG(&f->osm->log, OSM_LOG_ERROR,
				"ERR 4E04: realloc: %s\n", strerror(errno));
			goto out;
		}
		f->link = ptr;
		f->link_cnt_max = cnt_max;
		memset(&f->link[f->link_cnt], 0,
		       (f->link_cnt_max - f->link_cnt) * sizeof(*f->link));
	}
	l = calloc(1, sizeof(*l));
	if (!l) {
		OSM_LOG(&f->osm->log, OSM_LOG_ERROR,
			"ERR 4E05: calloc: %s\n", strerror(errno));
		goto out;
	}
	f->link[f->link_cnt++] = l;
out:
	return l;
}