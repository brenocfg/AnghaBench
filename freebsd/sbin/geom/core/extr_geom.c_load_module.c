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
 char* class_name ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ kldload (char*) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
load_module(void)
{
	char name1[64], name2[64];

	snprintf(name1, sizeof(name1), "g_%s", class_name);
	snprintf(name2, sizeof(name2), "geom_%s", class_name);
	if (modfind(name1) < 0) {
		/* Not present in kernel, try loading it. */
		if (kldload(name2) < 0 || modfind(name1) < 0) {
			if (errno != EEXIST) {
				err(EXIT_FAILURE, "cannot load %s", name2);
			}
		}
	}
}