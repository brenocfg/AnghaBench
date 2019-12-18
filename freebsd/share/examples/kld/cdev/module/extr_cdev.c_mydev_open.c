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
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  dev2udev (struct cdev*) ; 
 scalar_t__ len ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,int,struct proc*) ; 

int
mydev_open(struct cdev *dev, int flag, int otyp, struct thread *td)
{
    struct proc *procp = td->td_proc;

    printf("mydev_open: dev_t=%lu, flag=%x, otyp=%x, procp=%p\n",
	   dev2udev(dev), flag, otyp, procp);
    memset(&buf, '\0', 513);
    len = 0;
    return (0);
}