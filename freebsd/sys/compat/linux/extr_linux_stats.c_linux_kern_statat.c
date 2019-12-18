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
struct stat {int dummy; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int kern_statat (struct thread*,int,int,char*,int,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translate_vnhook_major_minor ; 

__attribute__((used)) static int
linux_kern_statat(struct thread *td, int flag, int fd, char *path,
    enum uio_seg pathseg, struct stat *sbp)
{

	return (kern_statat(td, flag, fd, path, pathseg, sbp,
	    translate_vnhook_major_minor));
}