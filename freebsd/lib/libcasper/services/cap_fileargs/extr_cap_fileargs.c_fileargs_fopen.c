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
typedef  int /*<<< orphan*/  fileargs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 int fileargs_open (int /*<<< orphan*/ *,char const*) ; 

FILE *
fileargs_fopen(fileargs_t *fa, const char *name, const char *mode)
{
	int fd;

	if ((fd = fileargs_open(fa, name)) < 0) {
		return (NULL);
	}

	return (fdopen(fd, mode));
}