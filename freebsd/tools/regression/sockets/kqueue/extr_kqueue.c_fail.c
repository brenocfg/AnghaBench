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
 int curtest ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strerror (int) ; 

__attribute__((used)) static void
fail(int error, const char *func, const char *socktype, const char *rest)
{

	printf("not ok %d\n", curtest);

	if (socktype == NULL)
		printf("# %s(): %s\n", func, strerror(error));
	else if (rest == NULL)
		printf("# %s(%s): %s\n", func, socktype,
		    strerror(error));
	else
		printf("# %s(%s, %s): %s\n", func, socktype, rest,
		    strerror(error));
	exit(-1);
}