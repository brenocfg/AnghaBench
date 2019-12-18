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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int for_each_note (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marksfilename ; 
 int /*<<< orphan*/  note2mark_cb ; 
 int /*<<< orphan*/ * xfopen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void regenerate_marks(void)
{
	int ret;
	FILE *marksfile = xfopen(marksfilename, "w+");

	ret = for_each_note(NULL, 0, note2mark_cb, marksfile);
	if (ret)
		die("Regeneration of marks failed, returned %d.", ret);
	fclose(marksfile);
}