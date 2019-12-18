#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct configuration_entry* entry_name; } ;
struct TYPE_12__ {TYPE_5__ cep; } ;
struct TYPE_9__ {struct configuration_entry* entry_name; } ;
struct TYPE_10__ {TYPE_3__ cep; } ;
struct TYPE_7__ {struct configuration_entry* entry_name; } ;
struct TYPE_8__ {TYPE_1__ cep; } ;
struct configuration_entry {struct configuration_entry* mp_cache_entries; TYPE_6__ mp_cache_params; TYPE_4__ negative_cache_params; TYPE_2__ positive_cache_params; struct configuration_entry* name; int /*<<< orphan*/  mp_cache_lock; int /*<<< orphan*/  negative_cache_lock; int /*<<< orphan*/  positive_cache_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration_entry*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration_entry*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct configuration_entry*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void
destroy_configuration_entry(struct configuration_entry *entry)
{
	TRACE_IN(destroy_configuration_entry);
	assert(entry != NULL);
	pthread_mutex_destroy(&entry->positive_cache_lock);
	pthread_mutex_destroy(&entry->negative_cache_lock);
	pthread_mutex_destroy(&entry->mp_cache_lock);
	free(entry->name);
	free(entry->positive_cache_params.cep.entry_name);
	free(entry->negative_cache_params.cep.entry_name);
	free(entry->mp_cache_params.cep.entry_name);
	free(entry->mp_cache_entries);
	free(entry);
	TRACE_OUT(destroy_configuration_entry);
}