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
struct child_process {int dummy; } ;
struct subprocess_entry {struct child_process process; } ;
struct subprocess_capability {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 scalar_t__ handshake_capabilities (struct child_process*,struct subprocess_capability*,unsigned int*) ; 
 scalar_t__ handshake_version (struct child_process*,char const*,int*,int*) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int subprocess_handshake(struct subprocess_entry *entry,
			 const char *welcome_prefix,
			 int *versions,
			 int *chosen_version,
			 struct subprocess_capability *capabilities,
			 unsigned int *supported_capabilities)
{
	int retval;
	struct child_process *process = &entry->process;

	sigchain_push(SIGPIPE, SIG_IGN);

	retval = handshake_version(process, welcome_prefix, versions,
				   chosen_version) ||
		 handshake_capabilities(process, capabilities,
					supported_capabilities);

	sigchain_pop(SIGPIPE);
	return retval;
}