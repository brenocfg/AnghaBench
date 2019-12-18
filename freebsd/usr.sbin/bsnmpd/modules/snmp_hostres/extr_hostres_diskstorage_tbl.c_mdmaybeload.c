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
typedef  int /*<<< orphan*/  name2 ;
typedef  int /*<<< orphan*/  name1 ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* MD_NAME ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int kldload (char*) ; 
 int modfind (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
mdmaybeload(void)
{
	char name1[64], name2[64];

	snprintf(name1, sizeof(name1), "g_%s", MD_NAME);
	snprintf(name2, sizeof(name2), "geom_%s", MD_NAME);
	if (modfind(name1) == -1) {
		/* Not present in kernel, try loading it. */
		if (kldload(name2) == -1 || modfind(name1) == -1) {
			if (errno != EEXIST) {
				errx(EXIT_FAILURE,
				    "%s module not available!", name2);
			}
		}
	}
}