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
 int /*<<< orphan*/  DPRINTF (int,int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  File_list ; 
 scalar_t__ Fort_len ; 
 int /*<<< orphan*/  Fortbuf ; 
 int Found_one ; 
 int /*<<< orphan*/  do_malloc (unsigned int) ; 
 int /*<<< orphan*/  matches_in_list (int /*<<< orphan*/ ) ; 
 scalar_t__ maxlen_in_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
find_matches(void)
{
	Fort_len = maxlen_in_list(File_list);
	DPRINTF(2, (stderr, "Maximum length is %d\n", Fort_len));
	/* extra length, "%\n" is appended */
	Fortbuf = do_malloc((unsigned int) Fort_len + 10);

	Found_one = FALSE;
	matches_in_list(File_list);

	return (Found_one);
}