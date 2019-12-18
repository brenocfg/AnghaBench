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
struct filecaps {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int PD_CLOEXEC ; 
 int falloc_caps (struct thread*,struct file**,int*,int,struct filecaps*) ; 

int
procdesc_falloc(struct thread *td, struct file **resultfp, int *resultfd,
    int flags, struct filecaps *fcaps)
{
	int fflags;

	fflags = 0;
	if (flags & PD_CLOEXEC)
		fflags = O_CLOEXEC;

	return (falloc_caps(td, resultfp, resultfd, fflags, fcaps));
}