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
struct mqueue {int dummy; } ;
struct mqfs_node {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int _getmq (struct thread*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct file**,struct mqfs_node**,struct mqueue**) ; 
 int /*<<< orphan*/  cap_write_rights ; 
 int /*<<< orphan*/  fget_write ; 

__attribute__((used)) static __inline int
getmq_write(struct thread *td, int fd, struct file **fpp,
	struct mqfs_node **ppn, struct mqueue **pmq)
{

	return _getmq(td, fd, &cap_write_rights, fget_write,
	    fpp, ppn, pmq);
}