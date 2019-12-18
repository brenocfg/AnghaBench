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
struct split_file {int /*<<< orphan*/  curfd; } ;
struct open_file {scalar_t__ f_fsdata; } ;

/* Variables and functions */
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int
splitfs_stat(struct open_file *f, struct stat *sb)
{
    int	result;
    struct split_file *sf = (struct split_file *)f->f_fsdata;

    /* stat as normal, but indicate that size is unknown */
    if ((result = fstat(sf->curfd, sb)) == 0)
	sb->st_size = -1;
    return (result);
}