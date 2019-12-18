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
typedef  int /*<<< orphan*/  u_int32 ;
struct TYPE_2__ {int l_ui; int l_uf; } ;
struct recvbuf {TYPE_1__ recv_time; int /*<<< orphan*/  recv_srcadr; } ;

/* Variables and functions */
 int /*<<< orphan*/  derive_nonce (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generate_nonce(
	struct recvbuf *	rbufp,
	char *			nonce,
	size_t			nonce_octets
	)
{
	u_int32 derived;

	derived = derive_nonce(&rbufp->recv_srcadr,
			       rbufp->recv_time.l_ui,
			       rbufp->recv_time.l_uf);
	snprintf(nonce, nonce_octets, "%08x%08x%08x",
		 rbufp->recv_time.l_ui, rbufp->recv_time.l_uf, derived);
}