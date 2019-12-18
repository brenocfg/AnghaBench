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
struct rsn_pmksa_cache_entry {int dummy; } ;

/* Variables and functions */
 struct rsn_pmksa_cache_entry* pmksa_cache_head (int /*<<< orphan*/ ) ; 

struct rsn_pmksa_cache_entry * wpa_sm_pmksa_cache_head(struct wpa_sm *sm)
{
	return pmksa_cache_head(sm->pmksa);
}