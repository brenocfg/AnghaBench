#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32 ;
typedef  scalar_t__ u_int ;
struct recvbuf {int /*<<< orphan*/  recv_srcadr; } ;
struct TYPE_5__ {int l_ui; void* l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  L_SUB (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ derive_nonce (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  get_systime (TYPE_1__*) ; 
 int sscanf (char const*,char*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int validate_nonce(
	const char *		pnonce,
	struct recvbuf *	rbufp
	)
{
	u_int	ts_i;
	u_int	ts_f;
	l_fp	ts;
	l_fp	now_delta;
	u_int	supposed;
	u_int	derived;

	if (3 != sscanf(pnonce, "%08x%08x%08x", &ts_i, &ts_f, &supposed))
		return FALSE;

	ts.l_ui = (u_int32)ts_i;
	ts.l_uf = (u_int32)ts_f;
	derived = derive_nonce(&rbufp->recv_srcadr, ts.l_ui, ts.l_uf);
	get_systime(&now_delta);
	L_SUB(&now_delta, &ts);

	return (supposed == derived && now_delta.l_ui < 16);
}