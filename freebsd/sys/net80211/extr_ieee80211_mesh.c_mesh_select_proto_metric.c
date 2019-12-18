#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_mesh_state {TYPE_1__* ms_pmetric; } ;
struct TYPE_3__ {int /*<<< orphan*/  mpm_descr; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_1__* mesh_proto_metrics ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
mesh_select_proto_metric(struct ieee80211vap *vap, const char *name)
{
	struct ieee80211_mesh_state *ms = vap->iv_mesh;
	int i;

	for (i = 0; i < nitems(mesh_proto_metrics); i++) {
		if (strcasecmp(mesh_proto_metrics[i].mpm_descr, name) == 0) {
			ms->ms_pmetric = &mesh_proto_metrics[i];
			return 0;
		}
	}
	return ENOENT;
}