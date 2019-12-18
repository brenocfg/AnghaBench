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
struct runtime_env {int /*<<< orphan*/  sockfd; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct runtime_env*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct runtime_env*)) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct runtime_env*) ; 

__attribute__((used)) static void
destroy_runtime_env(struct runtime_env *env)
{
	TRACE_IN(destroy_runtime_env);
	close(env->queue);
	close(env->sockfd);
	free(env);
	TRACE_OUT(destroy_runtime_env);
}