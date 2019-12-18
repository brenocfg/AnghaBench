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
typedef  int off_t ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int GIGABYTE ; 
 int KILOBYTE ; 
 int MEGABYTE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
gv_roughlength(off_t bytes, int lj)
{
	static char desc[16];
	
	/* Gigabytes. */
	if (bytes > (off_t)MEGABYTE * 10000)
		snprintf(desc, sizeof(desc), lj ? "%jd GB" : "%10jd GB",
		    bytes / GIGABYTE);

	/* Megabytes. */
	else if (bytes > KILOBYTE * 10000)
		snprintf(desc, sizeof(desc), lj ? "%jd MB" : "%10jd MB",
		    bytes / MEGABYTE);

	/* Kilobytes. */
	else if (bytes > 10000)
		snprintf(desc, sizeof(desc), lj ? "%jd kB" : "%10jd kB",
		    bytes / KILOBYTE);

	/* Bytes. */
	else
		snprintf(desc, sizeof(desc), lj ? "%jd  B" : "%10jd  B", bytes);

	return (desc);
}