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
 int EPERM ; 
 int FREAD ; 
 int FWRITE ; 
 int O_NONBLOCK ; 
 char* devtoname (struct cdev*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
xptopen(struct cdev *dev, int flags, int fmt, struct thread *td)
{

	/*
	 * Only allow read-write access.
	 */
	if (((flags & FWRITE) == 0) || ((flags & FREAD) == 0))
		return(EPERM);

	/*
	 * We don't allow nonblocking access.
	 */
	if ((flags & O_NONBLOCK) != 0) {
		printf("%s: can't do nonblocking access\n", devtoname(dev));
		return(ENODEV);
	}

	return(0);
}