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
struct unpcb {int dummy; } ;
struct socket {TYPE_1__* so_proto; } ;
struct file {scalar_t__ f_type; struct socket* f_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pr_domain; } ;

/* Variables and functions */
 scalar_t__ DTYPE_SOCKET ; 
 int /*<<< orphan*/  localdomain ; 
 struct unpcb* sotounpcb (struct socket*) ; 

__attribute__((used)) static struct unpcb *
fptounp(struct file *fp)
{
	struct socket *so;

	if (fp->f_type != DTYPE_SOCKET)
		return (NULL);
	if ((so = fp->f_data) == NULL)
		return (NULL);
	if (so->so_proto->pr_domain != &localdomain)
		return (NULL);
	return sotounpcb(so);
}