#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {int c_type; int c_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_BSIZE ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int mapsize ; 
 TYPE_1__ spcl ; 
 int /*<<< orphan*/  writeheader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writerec (char*,int /*<<< orphan*/ ) ; 

void
dumpmap(char *map, int type, ino_t ino)
{
	int i;
	char *cp;

	spcl.c_type = type;
	spcl.c_count = howmany(mapsize * sizeof(char), TP_BSIZE);
	writeheader(ino);
	for (i = 0, cp = map; i < spcl.c_count; i++, cp += TP_BSIZE)
		writerec(cp, 0);
}