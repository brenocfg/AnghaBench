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
struct g_command {unsigned int gc_flags; } ;

/* Variables and functions */
 unsigned int G_FLAG_VERBOSE ; 
 scalar_t__ verbose ; 

__attribute__((used)) static unsigned
set_flags(struct g_command *cmd)
{
	unsigned flags = 0;

	if ((cmd->gc_flags & G_FLAG_VERBOSE) != 0 && verbose)
		flags |= G_FLAG_VERBOSE;

	return (flags);
}