#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct torus {TYPE_2__* osm; int /*<<< orphan*/  seed_cnt; TYPE_1__* seed; } ;
struct link {TYPE_3__* end; } ;
typedef  void* guid_t ;
struct TYPE_6__ {int port; int /*<<< orphan*/ * link; int /*<<< orphan*/ * sw; void* n_id; void* type; } ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;
struct TYPE_4__ {struct link zp_link; struct link zm_link; struct link yp_link; struct link ym_link; struct link xp_link; struct link xm_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 void* PASSTHRU ; 
 int /*<<< orphan*/  parse_guid (struct torus*,void**,char const*) ; 

__attribute__((used)) static
bool parse_dir_link(int c_dir, struct torus *t, const char *parse_sep)
{
	guid_t sw_guid0, sw_guid1;
	struct link *l;
	bool success = false;

	if (!parse_guid(t, &sw_guid0, parse_sep))
		goto out;

	if (!parse_guid(t, &sw_guid1, parse_sep))
		goto out;

	if (!t) {
		success = true;
		goto out;
	}

	switch (c_dir) {
	case -1:
		l = &t->seed[t->seed_cnt - 1].xm_link;
		break;
	case  1:
		l = &t->seed[t->seed_cnt - 1].xp_link;
		break;
	case -2:
		l = &t->seed[t->seed_cnt - 1].ym_link;
		break;
	case  2:
		l = &t->seed[t->seed_cnt - 1].yp_link;
		break;
	case -3:
		l = &t->seed[t->seed_cnt - 1].zm_link;
		break;
	case  3:
		l = &t->seed[t->seed_cnt - 1].zp_link;
		break;
	default:
		OSM_LOG(&t->osm->log, OSM_LOG_ERROR,
			"ERR 4E0E: unknown link direction %d\n", c_dir);
		goto out;
	}
	l->end[0].type = PASSTHRU;
	l->end[0].port = -1;		/* We don't really connect. */
	l->end[0].n_id = sw_guid0;
	l->end[0].sw = NULL;		/* Fix this up later. */
	l->end[0].link = NULL;		/* Fix this up later. */

	l->end[1].type = PASSTHRU;
	l->end[1].port = -1;		/* We don't really connect. */
	l->end[1].n_id = sw_guid1;
	l->end[1].sw = NULL;		/* Fix this up later. */
	l->end[1].link = NULL;		/* Fix this up later. */

	success = true;
out:
	return success;
}