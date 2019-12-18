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
struct configuration {unsigned int entries_size; int /*<<< orphan*/  rwlock; struct configuration* entries; struct configuration* socket_path; struct configuration* pidfile_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_configuration_entry (struct configuration) ; 
 int /*<<< orphan*/  free (struct configuration*) ; 
 int /*<<< orphan*/  pthread_rwlock_destroy (int /*<<< orphan*/ *) ; 

void
destroy_configuration(struct configuration *config)
{
	unsigned int i;

	TRACE_IN(destroy_configuration);
	assert(config != NULL);
	free(config->pidfile_path);
	free(config->socket_path);

	for (i = 0; i < config->entries_size; ++i)
		destroy_configuration_entry(config->entries[i]);
	free(config->entries);

	pthread_rwlock_destroy(&config->rwlock);
	free(config);
	TRACE_OUT(destroy_configuration);
}