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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IWOTH ; 
 int /*<<< orphan*/  bitset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ stat (char*,struct stat*) ; 

char *
ttypath()
{
	struct stat stbuf;
	register char *pathn;
	extern char *ttyname();
	extern char *getlogin();

	/* compute the pathname of the controlling tty */
	if ((pathn = ttyname(2)) == NULL && (pathn = ttyname(1)) == NULL &&
	    (pathn = ttyname(0)) == NULL)
	{
		errno = 0;
		return NULL;
	}

	/* see if we have write permission */
	if (stat(pathn, &stbuf) < 0 || !bitset(S_IWOTH, stbuf.st_mode))
	{
		errno = 0;
		return NULL;
	}

	/* see if the user is logged in */
	if (getlogin() == NULL)
		return NULL;

	/* looks good */
	return pathn;
}