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
struct wpa_sm {int /*<<< orphan*/  pmksa; } ;

/* Variables and functions */
 int pmksa_cache_list (int /*<<< orphan*/ ,char*,size_t) ; 

int wpa_sm_pmksa_cache_list(struct wpa_sm *sm, char *buf, size_t len)
{
	return pmksa_cache_list(sm->pmksa, buf, len);
}