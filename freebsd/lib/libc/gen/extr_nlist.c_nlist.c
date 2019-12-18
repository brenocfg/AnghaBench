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
struct nlist {int dummy; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int __fdnlist (int,struct nlist*) ; 
 int /*<<< orphan*/  _close (int) ; 
 int _open (char const*,int,int /*<<< orphan*/ ) ; 

int
nlist(const char *name, struct nlist *list)
{
	int fd, n;

	fd = _open(name, O_RDONLY | O_CLOEXEC, 0);
	if (fd < 0)
		return (-1);
	n = __fdnlist(fd, list);
	(void)_close(fd);
	return (n);
}