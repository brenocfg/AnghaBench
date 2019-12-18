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
struct ieee80211_mesh_proto_path {int /*<<< orphan*/  mpp_descr; } ;
struct TYPE_4__ {int mpp_active; int /*<<< orphan*/  mpp_descr; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IEEE80211_MESH_PROTO_DSZ ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct ieee80211_mesh_proto_path const*,int) ; 
 TYPE_1__* mesh_proto_paths ; 
 int nitems (TYPE_1__*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ieee80211_mesh_register_proto_path(const struct ieee80211_mesh_proto_path *mpp)
{
	int i, firstempty = -1;

	for (i = 0; i < nitems(mesh_proto_paths); i++) {
		if (strncmp(mpp->mpp_descr, mesh_proto_paths[i].mpp_descr,
		    IEEE80211_MESH_PROTO_DSZ) == 0)
			return EEXIST;
		if (!mesh_proto_paths[i].mpp_active && firstempty == -1)
			firstempty = i;
	}
	if (firstempty < 0)
		return ENOSPC;
	memcpy(&mesh_proto_paths[firstempty], mpp, sizeof(*mpp));
	mesh_proto_paths[firstempty].mpp_active = 1;
	return 0;
}