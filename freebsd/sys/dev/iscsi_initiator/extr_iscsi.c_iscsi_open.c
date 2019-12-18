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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  debug (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 scalar_t__ dev2unit (struct cdev*) ; 
 scalar_t__ max_sessions ; 

__attribute__((used)) static int
iscsi_open(struct cdev *dev, int flags, int otype, struct thread *td)
{
     debug_called(8);

     debug(7, "dev=%d", dev2unit(dev));

     if(dev2unit(dev) > max_sessions) {
	  // should not happen
          return ENODEV;
     }
     return 0;
}