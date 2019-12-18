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
typedef  int ssize_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
printlink(char *name)
{
	ssize_t lnklen;
	char path[MAXPATHLEN];

	if ((lnklen = readlink(name, path, MAXPATHLEN - 1)) == -1) {
		warn("%s", name);
		return;
	}
	path[lnklen] = '\0';
	(void)printf(" -> %s", path);
}