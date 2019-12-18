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
typedef  int /*<<< orphan*/  u8 ;
struct wps_registrar {struct wps_pbc_session* pbc_sessions; } ;
struct os_reltime {int dummy; } ;
struct wps_pbc_session {struct wps_pbc_session* next; struct os_reltime timestamp; int /*<<< orphan*/  uuid_e; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WPS_PBC_WALK_TIME ; 
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  os_get_reltime (struct os_reltime*) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_reltime_expired (struct os_reltime*,struct os_reltime*,int /*<<< orphan*/ ) ; 
 struct wps_pbc_session* os_zalloc (int) ; 
 int /*<<< orphan*/  wps_free_pbc_sessions (struct wps_pbc_session*) ; 

__attribute__((used)) static void wps_registrar_add_pbc_session(struct wps_registrar *reg,
					  const u8 *addr, const u8 *uuid_e)
{
	struct wps_pbc_session *pbc, *prev = NULL;
	struct os_reltime now;

	os_get_reltime(&now);

	pbc = reg->pbc_sessions;
	while (pbc) {
		if (os_memcmp(pbc->addr, addr, ETH_ALEN) == 0 &&
		    os_memcmp(pbc->uuid_e, uuid_e, WPS_UUID_LEN) == 0) {
			if (prev)
				prev->next = pbc->next;
			else
				reg->pbc_sessions = pbc->next;
			break;
		}
		prev = pbc;
		pbc = pbc->next;
	}

	if (!pbc) {
		pbc = os_zalloc(sizeof(*pbc));
		if (pbc == NULL)
			return;
		os_memcpy(pbc->addr, addr, ETH_ALEN);
		if (uuid_e)
			os_memcpy(pbc->uuid_e, uuid_e, WPS_UUID_LEN);
	}

	pbc->next = reg->pbc_sessions;
	reg->pbc_sessions = pbc;
	pbc->timestamp = now;

	/* remove entries that have timed out */
	prev = pbc;
	pbc = pbc->next;

	while (pbc) {
		if (os_reltime_expired(&now, &pbc->timestamp,
				       WPS_PBC_WALK_TIME)) {
			prev->next = NULL;
			wps_free_pbc_sessions(pbc);
			break;
		}
		prev = pbc;
		pbc = pbc->next;
	}
}