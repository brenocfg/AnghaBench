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
struct wpa_sm {int dummy; } ;
typedef  void rsn_pmksa_cache ;

/* Variables and functions */

__attribute__((used)) static inline struct rsn_pmksa_cache *
pmksa_cache_init(void (*free_cb)(struct rsn_pmksa_cache_entry *entry,
				 void *ctx, enum pmksa_free_reason reason),
		 void *ctx, struct wpa_sm *sm)
{
	return (void *) -1;
}