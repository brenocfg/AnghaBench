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

/* Variables and functions */
 int EEXIST ; 
 int EPROTONOSUPPORT ; 
 int IPPROTO_SEND ; 
 int /*<<< orphan*/  PRIV_NETINET_RAW ; 
 int /*<<< orphan*/  SEND_LOCK () ; 
 int /*<<< orphan*/  SEND_UNLOCK () ; 
 struct socket* V_send_so ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_recvspace ; 
 int /*<<< orphan*/  send_sendspace ; 
 int soreserve (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
send_attach(struct socket *so, int proto, struct thread *td)
{
	int error;

	SEND_LOCK();
	if (V_send_so != NULL) {
		SEND_UNLOCK();
		return (EEXIST);
	}

	error = priv_check(td, PRIV_NETINET_RAW);
	if (error) {
		SEND_UNLOCK();
		return(error);
	}

	if (proto != IPPROTO_SEND) {
		SEND_UNLOCK();
		return (EPROTONOSUPPORT);
	}
	error = soreserve(so, send_sendspace, send_recvspace);
	if (error) {
		SEND_UNLOCK();
		return(error);
	}

	V_send_so = so;
	SEND_UNLOCK();

	return (0);
}