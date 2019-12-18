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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ngc_connect(struct socket *so, struct sockaddr *nam, struct thread *td)
{
	/*
	 * At this time refuse to do this.. it used to
	 * do something but it was undocumented and not used.
	 */
	printf("program tried to connect control socket to remote node\n");
	return (EINVAL);
}