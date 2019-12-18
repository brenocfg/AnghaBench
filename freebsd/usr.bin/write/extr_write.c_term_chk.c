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
typedef  int /*<<< orphan*/  time_t ;
struct stat {int st_mode; int /*<<< orphan*/  st_atime; } ;

/* Variables and functions */
 int S_IWRITE ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 scalar_t__ fstatat (int,char*,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,char*) ; 

int
term_chk(int devfd, char *tty, int *msgsokP, time_t *atimeP, int showerror)
{
	struct stat s;

	if (fstatat(devfd, tty, &s, 0) < 0) {
		if (showerror)
			warn("%s%s", _PATH_DEV, tty);
		return(1);
	}
	*msgsokP = (s.st_mode & (S_IWRITE >> 3)) != 0;	/* group write bit */
	*atimeP = s.st_atime;
	return(0);
}