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
struct split_file {int curfd; } ;
struct open_file {scalar_t__ f_fsdata; } ;

/* Variables and functions */
 int close (int) ; 
 int /*<<< orphan*/  split_file_destroy (struct split_file*) ; 

__attribute__((used)) static int
splitfs_close(struct open_file *f)
{
    int fd;
    struct split_file *sf;

    sf = (struct split_file *)f->f_fsdata;
    fd = sf->curfd;
    split_file_destroy(sf);
    return(close(fd));
}