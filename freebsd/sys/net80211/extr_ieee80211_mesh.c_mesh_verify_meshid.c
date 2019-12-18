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
typedef  scalar_t__ uint8_t ;
struct ieee80211vap {struct ieee80211_mesh_state* iv_mesh; } ;
struct ieee80211_mesh_state {scalar_t__ const ms_idlen; int /*<<< orphan*/  ms_id; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__ const) ; 

__attribute__((used)) static int
mesh_verify_meshid(struct ieee80211vap *vap, const uint8_t *ie)
{
	struct ieee80211_mesh_state *ms = vap->iv_mesh;

	if (ie == NULL || ie[1] != ms->ms_idlen)
		return 1;
	return memcmp(ms->ms_id, ie + 2, ms->ms_idlen);
}