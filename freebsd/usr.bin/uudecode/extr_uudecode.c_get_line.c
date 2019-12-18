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
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infile ; 
 int /*<<< orphan*/  infp ; 
 int /*<<< orphan*/  outfile ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_line(char *buf, size_t size)
{

	if (fgets(buf, size, infp) != NULL)
		return (2);
	if (rflag)
		return (0);
	warnx("%s: %s: short file", infile, outfile);
	return (1);
}