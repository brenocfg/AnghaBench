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
struct wpa_supplicant {TYPE_4__* mesh_rsn; TYPE_3__* ifmsh; } ;
struct sae_data {int /*<<< orphan*/  group; } ;
struct TYPE_8__ {size_t sae_group_index; } ;
struct TYPE_7__ {TYPE_2__** bss; } ;
struct TYPE_6__ {TYPE_1__* conf; } ;
struct TYPE_5__ {int* sae_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  index_within_array (int*,size_t) ; 
 scalar_t__ sae_set_group (struct sae_data*,int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mesh_rsn_sae_group(struct wpa_supplicant *wpa_s,
			      struct sae_data *sae)
{
	int *groups = wpa_s->ifmsh->bss[0]->conf->sae_groups;

	/* Configuration may have changed, so validate current index */
	if (!index_within_array(groups, wpa_s->mesh_rsn->sae_group_index))
		return -1;

	for (;;) {
		int group = groups[wpa_s->mesh_rsn->sae_group_index];

		if (group <= 0)
			break;
		if (sae_set_group(sae, group) == 0) {
			wpa_dbg(wpa_s, MSG_DEBUG, "SME: Selected SAE group %d",
				sae->group);
			return 0;
		}
		wpa_s->mesh_rsn->sae_group_index++;
	}

	return -1;
}