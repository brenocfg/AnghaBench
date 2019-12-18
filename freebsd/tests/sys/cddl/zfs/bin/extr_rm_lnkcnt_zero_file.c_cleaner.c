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
 scalar_t__ ENOENT ; 
 scalar_t__ TRUE ; 
 scalar_t__ errno ; 
 char* filebase ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pickidx () ; 
 int remove (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static void *
cleaner(void *a)
{
	char buf[256];
	int idx, ret;

	while (TRUE) {
		idx = pickidx();
		(void) sprintf(buf, "%s.%03d", filebase, idx);
		ret = remove(buf);
		if (ret < 0 && errno != ENOENT)
			(void) perror("removing file");
	}

	return (NULL);
}