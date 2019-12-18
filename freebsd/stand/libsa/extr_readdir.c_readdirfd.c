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
struct open_file {int f_flags; TYPE_1__* f_ops; } ;
struct dirent {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* fo_readdir ) (struct open_file*,struct dirent*) ;} ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EIO ; 
 int F_RAW ; 
 int F_READ ; 
 unsigned int SOPEN_MAX ; 
 scalar_t__ errno ; 
 struct open_file* files ; 
 scalar_t__ stub1 (struct open_file*,struct dirent*) ; 

struct dirent *
readdirfd(int fd)
{
	static struct dirent dir;		/* XXX not thread safe */
	struct open_file *f = &files[fd];

	if ((unsigned)fd >= SOPEN_MAX || !(f->f_flags & F_READ)) {
		errno = EBADF;
		return (NULL);
	}
	if (f->f_flags & F_RAW) {
		errno = EIO;
		return (NULL);
	}
	errno = (f->f_ops->fo_readdir)(f, &dir);
	if (errno)
		return (NULL);
	return (&dir);
}