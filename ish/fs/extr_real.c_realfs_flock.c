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
struct fd {int /*<<< orphan*/  real_fd; } ;

/* Variables and functions */
 int LOCK_EX ; 
 int LOCK_EX_ ; 
 int LOCK_NB ; 
 int LOCK_NB_ ; 
 int LOCK_SH ; 
 int LOCK_SH_ ; 
 int LOCK_UN ; 
 int LOCK_UN_ ; 
 int flock (int /*<<< orphan*/ ,int) ; 

int realfs_flock(struct fd *fd, int operation) {
    int real_op = 0;
    if (operation & LOCK_SH_) real_op |= LOCK_SH;
    if (operation & LOCK_EX_) real_op |= LOCK_EX;
    if (operation & LOCK_UN_) real_op |= LOCK_UN;
    if (operation & LOCK_NB_) real_op |= LOCK_NB;
    return flock(fd->real_fd, real_op);
}