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
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 int DIP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFDIR ; 
 int IFMT ; 
 int /*<<< orphan*/  curinode ; 
 scalar_t__ curinum ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
checkactivedir(void)
{
    if (!curinode) {
	warnx("no current inode\n");
	return 0;
    }
    if ((DIP(curinode, di_mode) & IFMT) != IFDIR) {
	warnx("inode %ju not a directory", (uintmax_t)curinum);
	return 0;
    }
    return 1;
}