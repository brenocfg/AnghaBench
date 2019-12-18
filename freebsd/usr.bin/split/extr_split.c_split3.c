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
struct stat {int st_size; } ;

/* Variables and functions */
 int bytecnt ; 
 int chunks ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  ifd ; 
 int /*<<< orphan*/  split1 () ; 

__attribute__((used)) static void
split3(void)
{
	struct stat sb;

	if (fstat(ifd, &sb) == -1) {
		err(1, "stat");
		/* NOTREACHED */
	}

	if (chunks > sb.st_size) {
		errx(1, "can't split into more than %d files",
		    (int)sb.st_size);
		/* NOTREACHED */
	}

	bytecnt = sb.st_size / chunks;
	split1();
}