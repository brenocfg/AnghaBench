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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  utmpidlearr ;
typedef  int /*<<< orphan*/  up ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  RUSERSPROC_NAMES ; 
 int /*<<< orphan*/  RUSERSPROG ; 
 int /*<<< orphan*/  RUSERSVERS_IDLE ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval) ; 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 char* clnt_spcreateerror (char*) ; 
 char* clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rusers_reply (int /*<<< orphan*/ *,struct sockaddr_in*) ; 
 scalar_t__ xdr_utmpidlearr ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
onehost(char *host)
{
	utmpidlearr up;
	CLIENT *rusers_clnt;
	struct sockaddr_in addr;
	struct hostent *hp;
	struct timeval tv;

	hp = gethostbyname(host);
	if (hp == NULL)
		errx(1, "unknown host \"%s\"", host);

	rusers_clnt = clnt_create(host, RUSERSPROG, RUSERSVERS_IDLE, "udp");
	if (rusers_clnt == NULL)
		errx(1, "%s", clnt_spcreateerror(""));

	memset(&up, 0, sizeof(up));
	tv.tv_sec = 15;	/* XXX ?? */
	tv.tv_usec = 0;
	if (clnt_call(rusers_clnt, RUSERSPROC_NAMES, (xdrproc_t)xdr_void, NULL,
	    (xdrproc_t)xdr_utmpidlearr, &up, tv) != RPC_SUCCESS)
		errx(1, "%s", clnt_sperror(rusers_clnt, ""));
	memcpy(&addr.sin_addr.s_addr, hp->h_addr, sizeof(addr.sin_addr.s_addr));
	rusers_reply(&up, &addr);
	clnt_destroy(rusers_clnt);
}