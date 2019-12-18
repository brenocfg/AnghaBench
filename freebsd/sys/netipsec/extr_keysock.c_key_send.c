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
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int (* pru_send ) (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct thread*) ;} ;

/* Variables and functions */
 TYPE_1__ raw_usrreqs ; 
 int stub1 (struct socket*,int,struct mbuf*,struct sockaddr*,struct mbuf*,struct thread*) ; 

__attribute__((used)) static int
key_send(struct socket *so, int flags, struct mbuf *m, struct sockaddr *nam,
	 struct mbuf *control, struct thread *td)
{
	return(raw_usrreqs.pru_send(so, flags, m, nam, control, td));
}