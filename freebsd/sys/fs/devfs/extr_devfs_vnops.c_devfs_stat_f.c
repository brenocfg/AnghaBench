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
struct stat {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* fo_stat ) (struct file*,struct stat*,struct ucred*,struct thread*) ;} ;

/* Variables and functions */
 int stub1 (struct file*,struct stat*,struct ucred*,struct thread*) ; 
 TYPE_1__ vnops ; 

__attribute__((used)) static int
devfs_stat_f(struct file *fp, struct stat *sb, struct ucred *cred, struct thread *td)
{

	return (vnops.fo_stat(fp, sb, cred, td));
}