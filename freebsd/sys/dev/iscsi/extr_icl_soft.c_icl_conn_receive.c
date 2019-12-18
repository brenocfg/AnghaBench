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
typedef  int /*<<< orphan*/  uio ;
struct uio {size_t uio_resid; } ;
struct socket {int dummy; } ;
struct mbuf {int dummy; } ;
struct icl_conn {struct socket* ic_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_DEBUG (char*,...) ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  memset (struct uio*,int /*<<< orphan*/ ,int) ; 
 int soreceive (struct socket*,int /*<<< orphan*/ *,struct uio*,struct mbuf**,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static struct mbuf *
icl_conn_receive(struct icl_conn *ic, size_t len)
{
	struct uio uio;
	struct socket *so;
	struct mbuf *m;
	int error, flags;

	so = ic->ic_socket;

	memset(&uio, 0, sizeof(uio));
	uio.uio_resid = len;

	flags = MSG_DONTWAIT;
	error = soreceive(so, NULL, &uio, &m, NULL, &flags);
	if (error != 0) {
		ICL_DEBUG("soreceive error %d", error);
		return (NULL);
	}
	if (uio.uio_resid != 0) {
		m_freem(m);
		ICL_DEBUG("short read");
		return (NULL);
	}

	return (m);
}