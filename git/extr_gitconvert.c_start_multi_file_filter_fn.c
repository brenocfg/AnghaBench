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
struct subprocess_entry {int dummy; } ;
struct subprocess_capability {char* member_0; int /*<<< orphan*/  member_1; } ;
struct cmd2process {int /*<<< orphan*/  supported_capabilities; } ;

/* Variables and functions */
#define  CAP_CLEAN 130 
#define  CAP_DELAY 129 
#define  CAP_SMUDGE 128 
 int subprocess_handshake (struct subprocess_entry*,char*,int*,int /*<<< orphan*/ *,struct subprocess_capability*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_multi_file_filter_fn(struct subprocess_entry *subprocess)
{
	static int versions[] = {2, 0};
	static struct subprocess_capability capabilities[] = {
		{ "clean",  CAP_CLEAN  },
		{ "smudge", CAP_SMUDGE },
		{ "delay",  CAP_DELAY  },
		{ NULL, 0 }
	};
	struct cmd2process *entry = (struct cmd2process *)subprocess;
	return subprocess_handshake(subprocess, "git-filter", versions, NULL,
				    capabilities,
				    &entry->supported_capabilities);
}