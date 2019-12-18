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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {long dd_size; long dd_loc; int /*<<< orphan*/  dd_fd; } ;
typedef  TYPE_1__ RST_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
rst_telldir(RST_DIR *dirp)
{
	return ((long)lseek(dirp->dd_fd,
	    (off_t)0, SEEK_CUR) - dirp->dd_size + dirp->dd_loc);
}