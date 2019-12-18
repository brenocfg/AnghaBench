#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct p2p_group {int beacon_update; TYPE_1__* noa; } ;
struct TYPE_5__ {scalar_t__ used; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_group_update_ies (struct p2p_group*) ; 
 TYPE_1__* wpabuf_alloc_copy (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  wpabuf_put_data (TYPE_1__*,int /*<<< orphan*/  const*,size_t) ; 
 size_t wpabuf_size (TYPE_1__*) ; 

int p2p_group_notif_noa(struct p2p_group *group, const u8 *noa,
			size_t noa_len)
{
	if (noa == NULL) {
		wpabuf_free(group->noa);
		group->noa = NULL;
	} else {
		if (group->noa) {
			if (wpabuf_size(group->noa) >= noa_len) {
				group->noa->used = 0;
				wpabuf_put_data(group->noa, noa, noa_len);
			} else {
				wpabuf_free(group->noa);
				group->noa = NULL;
			}
		}

		if (!group->noa) {
			group->noa = wpabuf_alloc_copy(noa, noa_len);
			if (group->noa == NULL)
				return -1;
		}
	}

	group->beacon_update = 1;
	p2p_group_update_ies(group);
	return 0;
}