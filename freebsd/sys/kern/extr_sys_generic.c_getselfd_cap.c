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
struct filedesc {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cap_event_rights ; 
 int fget_unlocked (struct filedesc*,int,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
getselfd_cap(struct filedesc *fdp, int fd, struct file **fpp)
{

	return (fget_unlocked(fdp, fd, &cap_event_rights, fpp, NULL));
}