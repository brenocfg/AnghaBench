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
 scalar_t__ EOF ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tf ; 

int
endttyent(void)
{
	int rval;

	/*
         * NB: Don't free `line' because getttynam()
	 * may still be referencing it
	 */
	if (tf) {
		rval = (fclose(tf) != EOF);
		tf = NULL;
		return (rval);
	}
	return (1);
}