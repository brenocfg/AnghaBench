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

/* Variables and functions */
 int /*<<< orphan*/  copy_till (scalar_t__,int) ; 
 int debug ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ input_lines ; 
 int /*<<< orphan*/  last_frozen_line ; 
 int /*<<< orphan*/ * ofp ; 
 int /*<<< orphan*/  say (char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
spew_output(void)
{
	int rv;

#ifdef DEBUGGING
	if (debug & 256)
		say("il=%ld lfl=%ld\n", input_lines, last_frozen_line);
#endif
	if (input_lines)
		copy_till(input_lines, true);	/* dump remainder of file */
	rv = ferror(ofp) == 0 && fclose(ofp) == 0;
	ofp = NULL;
	return rv;
}