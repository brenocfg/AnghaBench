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
 int MAXPATHS ; 
 char NCURSES_PATHSEP ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_DATABASE ; 
 scalar_t__ _nc_access (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
add_tc(char *termpaths[], char *path, int count)
{
    char *save = strchr(path, NCURSES_PATHSEP);
    if (save != 0)
	*save = '\0';
    if (count < MAXPATHS
	&& _nc_access(path, R_OK) == 0) {
	termpaths[count++] = path;
	TR(TRACE_DATABASE, ("Adding termpath %s", path));
    }
    termpaths[count] = 0;
    if (save != 0)
	*save = NCURSES_PATHSEP;
    return count;
}