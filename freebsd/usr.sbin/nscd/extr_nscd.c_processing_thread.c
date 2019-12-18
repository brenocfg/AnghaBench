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
struct processing_thread_args {int /*<<< orphan*/  the_configuration; int /*<<< orphan*/  the_runtime_env; int /*<<< orphan*/  the_cache; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR_1 (char*,char*) ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  TRACE_MSG (char*) ; 
 int /*<<< orphan*/  free (struct processing_thread_args*) ; 
 int /*<<< orphan*/  processing_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
processing_thread(void *data)
{
	struct processing_thread_args	*args;
	sigset_t new;

	TRACE_MSG("=> processing_thread");
	args = (struct processing_thread_args *)data;

	sigemptyset(&new);
	sigaddset(&new, SIGPIPE);
	if (pthread_sigmask(SIG_BLOCK, &new, NULL) != 0)
		LOG_ERR_1("processing thread",
			"thread can't block the SIGPIPE signal");

	processing_loop(args->the_cache, args->the_runtime_env,
		args->the_configuration);
	free(args);
	TRACE_MSG("<= processing_thread");

	return (NULL);
}