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
 int /*<<< orphan*/  pmksa_cache_flush (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void wpa_sm_pmksa_cache_flush(struct wpa_sm *sm, void *network_ctx)
{
	pmksa_cache_flush(sm->pmksa, network_ctx, NULL, 0);
}