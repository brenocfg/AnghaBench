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
struct configuration {int socket_mode; int force_unlink; size_t entries_size; int /*<<< orphan*/ * entries; int /*<<< orphan*/  threads_num; int /*<<< orphan*/  query_timeout; int /*<<< orphan*/ * pidfile_path; int /*<<< orphan*/ * socket_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PIDFILE_PATH ; 
 int /*<<< orphan*/  DEFAULT_QUERY_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_SOCKET_PATH ; 
 int /*<<< orphan*/  DEFAULT_THREADS_NUM ; 
 int S_IFSOCK ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct configuration*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct configuration*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  destroy_configuration_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

void
fill_configuration_defaults(struct configuration *config)
{
	size_t	len, i;

	TRACE_IN(fill_configuration_defaults);
	assert(config != NULL);

	if (config->socket_path != NULL)
		free(config->socket_path);

	len = strlen(DEFAULT_SOCKET_PATH);
	config->socket_path = calloc(1, len + 1);
	assert(config->socket_path != NULL);
	memcpy(config->socket_path, DEFAULT_SOCKET_PATH, len);

	len = strlen(DEFAULT_PIDFILE_PATH);
	config->pidfile_path = calloc(1, len + 1);
	assert(config->pidfile_path != NULL);
	memcpy(config->pidfile_path, DEFAULT_PIDFILE_PATH, len);

	config->socket_mode =  S_IFSOCK | S_IRUSR | S_IWUSR |
		S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	config->force_unlink = 1;

	config->query_timeout = DEFAULT_QUERY_TIMEOUT;
	config->threads_num = DEFAULT_THREADS_NUM;

	for (i = 0; i < config->entries_size; ++i)
		destroy_configuration_entry(config->entries[i]);
	config->entries_size = 0;

	TRACE_OUT(fill_configuration_defaults);
}