#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int _orientation; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCKFILE (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE (TYPE_1__*) ; 

int
fwide(FILE *fp, int mode)
{
	int m;

	FLOCKFILE(fp);
	/* Only change the orientation if the stream is not oriented yet. */
	if (mode != 0 && fp->_orientation == 0)
		fp->_orientation = mode > 0 ? 1 : -1;
	m = fp->_orientation;
	FUNLOCKFILE(fp);

	return (m);
}