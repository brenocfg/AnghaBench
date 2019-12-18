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
typedef  union u_spcl {int dummy; } u_spcl ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  Bcvt ; 
 int CHECKSUM ; 
 int FAIL ; 
 int GOOD ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ swabl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
checksum(int *buf)
{
	int i, j;

	j = sizeof(union u_spcl) / sizeof(int);
	i = 0;
	if (!Bcvt) {
		do
			i += *buf++;
		while (--j);
	} else {
		/* What happens if we want to read restore tapes
			for a 16bit int machine??? */
		do
			i += swabl(*buf++);
		while (--j);
	}

	if (i != CHECKSUM) {
		fprintf(stderr, "Checksum error %o, inode %ju file %s\n", i,
		    (uintmax_t)curfile.ino, curfile.name);
		return(FAIL);
	}
	return(GOOD);
}