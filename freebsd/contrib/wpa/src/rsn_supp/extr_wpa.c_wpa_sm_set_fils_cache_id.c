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
struct wpa_sm {int fils_cache_id_set; int /*<<< orphan*/  fils_cache_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILS_CACHE_ID_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void wpa_sm_set_fils_cache_id(struct wpa_sm *sm, const u8 *fils_cache_id)
{
#ifdef CONFIG_FILS
	if (sm && fils_cache_id) {
		sm->fils_cache_id_set = 1;
		os_memcpy(sm->fils_cache_id, fils_cache_id, FILS_CACHE_ID_LEN);
	}
#endif /* CONFIG_FILS */
}