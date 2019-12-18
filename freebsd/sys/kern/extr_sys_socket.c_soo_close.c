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
struct socket {int dummy; } ;
struct file {struct socket* f_data; int /*<<< orphan*/ * f_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  badfileops ; 
 int soclose (struct socket*) ; 

__attribute__((used)) static int
soo_close(struct file *fp, struct thread *td)
{
	int error = 0;
	struct socket *so;

	so = fp->f_data;
	fp->f_ops = &badfileops;
	fp->f_data = NULL;

	if (so)
		error = soclose(so);
	return (error);
}