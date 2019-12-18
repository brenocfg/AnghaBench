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
struct event_config_entry {int /*<<< orphan*/ * avoid_method; } ;
struct event_config {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct event_config_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct event_config_entry*) ; 
 struct event_config_entry* mm_malloc (int) ; 
 int /*<<< orphan*/ * mm_strdup (char const*) ; 
 int /*<<< orphan*/  next ; 

int
event_config_avoid_method(struct event_config *cfg, const char *method)
{
	struct event_config_entry *entry = mm_malloc(sizeof(*entry));
	if (entry == NULL)
		return (-1);

	if ((entry->avoid_method = mm_strdup(method)) == NULL) {
		mm_free(entry);
		return (-1);
	}

	TAILQ_INSERT_TAIL(&cfg->entries, entry, next);

	return (0);
}