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
 char* mkdtemp (char*) ; 
 int rmdir (char*) ; 

int
main(void)
{
	char	dirname[] = "/tmp/temp.XXXXXX";

	if (mkdtemp(dirname) != dirname)
		return 1;
	return rmdir(dirname) == -1;
}