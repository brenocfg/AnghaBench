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
struct wpa_group {scalar_t__ references; } ;
struct wpa_authenticator {struct wpa_group* group; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_group_free (struct wpa_authenticator*,struct wpa_group*) ; 

__attribute__((used)) static void wpa_group_put(struct wpa_authenticator *wpa_auth,
			  struct wpa_group *group)
{
	/* Skip the special first group */
	if (wpa_auth->group == group)
		return;

	group->references--;
	if (group->references)
		return;
	wpa_group_free(wpa_auth, group);
}