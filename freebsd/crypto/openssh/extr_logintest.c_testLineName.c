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
typedef  int /*<<< orphan*/  strip ;
typedef  int /*<<< orphan*/  full ;
typedef  int /*<<< orphan*/  abbrev ;

/* Variables and functions */
 int /*<<< orphan*/  line_abbrevname (char*,char*,int) ; 
 int /*<<< orphan*/  line_fullname (char*,char*,int) ; 
 int /*<<< orphan*/  line_stripname (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 

void
testLineName(char *line)
{
	/* have to null-terminate - these functions are designed for
	 * structures with fixed-length char arrays, and don't null-term.*/
	char full[17], strip[9], abbrev[5];

	memset(full, '\0', sizeof(full));
	memset(strip, '\0', sizeof(strip));
	memset(abbrev, '\0', sizeof(abbrev));

	line_fullname(full, line, sizeof(full)-1);
	line_stripname(strip, full, sizeof(strip)-1);
	line_abbrevname(abbrev, full, sizeof(abbrev)-1);
	printf("%s: %s, %s, %s\n", line, full, strip, abbrev);

}