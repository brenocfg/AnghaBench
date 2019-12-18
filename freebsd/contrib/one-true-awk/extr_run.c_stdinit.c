#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* fname; void* mode; int /*<<< orphan*/  fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOPEN_MAX ; 
 void* GT ; 
 void* LT ; 
 TYPE_1__* calloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/  nfiles ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

void stdinit(void)	/* in case stdin, etc., are not constants */
{
	nfiles = FOPEN_MAX;
	files = calloc(nfiles, sizeof(*files));
	if (files == NULL)
		FATAL("can't allocate file memory for %u files", nfiles);
        files[0].fp = stdin;
	files[0].fname = "/dev/stdin";
	files[0].mode = LT;
        files[1].fp = stdout;
	files[1].fname = "/dev/stdout";
	files[1].mode = GT;
        files[2].fp = stderr;
	files[2].fname = "/dev/stderr";
	files[2].mode = GT;
}