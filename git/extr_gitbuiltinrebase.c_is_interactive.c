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
struct rebase_options {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ REBASE_INTERACTIVE ; 
 scalar_t__ REBASE_PRESERVE_MERGES ; 

__attribute__((used)) static int is_interactive(struct rebase_options *opts)
{
	return opts->type == REBASE_INTERACTIVE ||
		opts->type == REBASE_PRESERVE_MERGES;
}