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
struct wps_pbc_session {struct wps_pbc_session* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wps_pbc_session*) ; 

__attribute__((used)) static void wps_free_pbc_sessions(struct wps_pbc_session *pbc)
{
	struct wps_pbc_session *prev;

	while (pbc) {
		prev = pbc;
		pbc = pbc->next;
		os_free(prev);
	}
}