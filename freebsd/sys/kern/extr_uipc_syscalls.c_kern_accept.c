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
struct sockaddr {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT4_INHERIT ; 
 int kern_accept4 (struct thread*,int,struct sockaddr**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct file**) ; 

int
kern_accept(struct thread *td, int s, struct sockaddr **name,
    socklen_t *namelen, struct file **fp)
{
	return (kern_accept4(td, s, name, namelen, ACCEPT4_INHERIT, fp));
}