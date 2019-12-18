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
typedef  int mode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int mkstemp (char*) ; 
 scalar_t__ tmpnam (char*) ; 
 scalar_t__ umask (int) ; 

__attribute__((used)) static FILE *
open_tempfile(char *filename)
{
    FILE *result = 0;

    _nc_STRCPY(filename, "/tmp/XXXXXX", PATH_MAX);
#if HAVE_MKSTEMP
    {
	int oldmask = (int) umask(077);
	int fd = mkstemp(filename);
	if (fd >= 0)
	    result = fdopen(fd, "w");
	umask((mode_t) oldmask);
    }
#else
    if (tmpnam(filename) != 0)
	result = fopen(filename, "w");
#endif
    return result;
}