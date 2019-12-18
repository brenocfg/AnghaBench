#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int (* fo_truncate ) (struct file*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ;} ;

/* Variables and functions */
 int stub1 (struct file*,int /*<<< orphan*/ ,struct ucred*,struct thread*) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
devfs_truncate_f(struct file *fp, off_t length, struct ucred *cred, struct thread *td)
{

	return (vnops.fo_truncate(fp, length, cred, td));
}