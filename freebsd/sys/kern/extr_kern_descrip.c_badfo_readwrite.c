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
struct uio {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBADF ; 

__attribute__((used)) static int
badfo_readwrite(struct file *fp, struct uio *uio, struct ucred *active_cred,
    int flags, struct thread *td)
{

	return (EBADF);
}