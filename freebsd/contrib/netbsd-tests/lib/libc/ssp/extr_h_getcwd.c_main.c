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
 int MAXPATHLEN ; 
 size_t atoi (char*) ; 
 int /*<<< orphan*/  getcwd (char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
main(int argc, char *argv[])
{
	char b[MAXPATHLEN];
	size_t len = atoi(argv[1]);
	(void)getcwd(b, len);
	(void)printf("%s\n", b);
	return 0;
}