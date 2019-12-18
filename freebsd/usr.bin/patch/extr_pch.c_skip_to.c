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
typedef  scalar_t__ off_t ;
typedef  scalar_t__ LINENUM ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ftello (int /*<<< orphan*/ ) ; 
 scalar_t__ p_base ; 
 scalar_t__ p_input_line ; 
 int /*<<< orphan*/  pfp ; 
 size_t pgets (int) ; 
 int /*<<< orphan*/  say (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
skip_to(off_t file_pos, LINENUM file_line)
{
	size_t	len;

	if (p_base > file_pos)
		fatal("Internal error: seek %lld>%lld\n",
		   (long long)p_base, (long long)file_pos);
	if (verbose && p_base < file_pos) {
		fseeko(pfp, p_base, SEEK_SET);
		say("The text leading up to this was:\n--------------------------\n");
		while (ftello(pfp) < file_pos) {
			len = pgets(false);
			if (len == 0)
				fatal("Unexpected end of file\n");
			say("|%s", buf);
		}
		say("--------------------------\n");
	} else
		fseeko(pfp, file_pos, SEEK_SET);
	p_input_line = file_line - 1;
}