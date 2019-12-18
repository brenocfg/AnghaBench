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
struct event_config_entry {int dummy; } ;
struct event_config {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 struct event_config_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct event_config_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_config_entry_free (struct event_config_entry*) ; 
 int /*<<< orphan*/  mm_free (struct event_config*) ; 
 int /*<<< orphan*/  next ; 

void
event_config_free(struct event_config *cfg)
{
	struct event_config_entry *entry;

	while ((entry = TAILQ_FIRST(&cfg->entries)) != NULL) {
		TAILQ_REMOVE(&cfg->entries, entry, next);
		event_config_entry_free(entry);
	}
	mm_free(cfg);
}