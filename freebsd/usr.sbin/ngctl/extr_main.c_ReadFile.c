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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CMDRTN_OK ; 
 int DoParseCommand (char*) ; 
 int LINE_MAX ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static int
ReadFile(FILE *fp)
{
	char line[LINE_MAX];
	int num, rtn;

	for (num = 1; fgets(line, sizeof(line), fp) != NULL; num++) {
		if (*line == '#')
			continue;
		if ((rtn = DoParseCommand(line)) != 0) {
			warnx("line %d: error in file", num);
			return (rtn);
		}
	}
	return (CMDRTN_OK);
}