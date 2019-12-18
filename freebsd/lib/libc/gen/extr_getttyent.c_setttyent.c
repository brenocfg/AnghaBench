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
 int /*<<< orphan*/  MALLOCCHUNK ; 
 int /*<<< orphan*/  _PATH_TTYS ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lbsize ; 
 int /*<<< orphan*/ * line ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rewind (scalar_t__) ; 
 scalar_t__ tf ; 

int
setttyent(void)
{

	if (line == NULL) {
		if ((line = malloc(MALLOCCHUNK)) == NULL)
			return (0);
		lbsize = MALLOCCHUNK;
	}
	if (tf) {
		rewind(tf);
		return (1);
	} else if ( (tf = fopen(_PATH_TTYS, "re")) )
		return (1);
	return (0);
}