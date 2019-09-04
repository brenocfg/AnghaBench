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
struct rebase_options {int type; } ;

/* Variables and functions */
#define  REBASE_AM 131 
#define  REBASE_INTERACTIVE 130 
#define  REBASE_MERGE 129 
#define  REBASE_PRESERVE_MERGES 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void imply_interactive(struct rebase_options *opts, const char *option)
{
	switch (opts->type) {
	case REBASE_AM:
		die(_("%s requires an interactive rebase"), option);
		break;
	case REBASE_INTERACTIVE:
	case REBASE_PRESERVE_MERGES:
		break;
	case REBASE_MERGE:
		/* we now implement --merge via --interactive */
	default:
		opts->type = REBASE_INTERACTIVE; /* implied */
		break;
	}
}