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
 int /*<<< orphan*/  Error (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * myfopen (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

FILE *SafeOpenWrite (const char *filename)
{
	FILE	*f;

	f = myfopen(filename, "wb");

	if (!f)
		Error ("Error opening %s: %s",filename,strerror(errno));

	return f;
}