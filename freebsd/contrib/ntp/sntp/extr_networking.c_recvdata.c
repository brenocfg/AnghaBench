#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pkt {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
typedef  TYPE_1__ sockaddr_u ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  int GETSOCKNAME_SOCKLEN_TYPE ;

/* Variables and functions */
 int debug ; 
 int /*<<< orphan*/  pkt_output (struct pkt*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int recvfrom (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 char* sptoa (TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 

int
recvdata(
	SOCKET		rsock,
	sockaddr_u *	sender,
	void *		rdata,
	int		rdata_length
	)
{
	GETSOCKNAME_SOCKLEN_TYPE slen;
	int recvc;

	slen = sizeof(*sender);
	recvc = recvfrom(rsock, rdata, rdata_length, 0,
			 &sender->sa, &slen);
	if (recvc < 0)
		return recvc;
#ifdef DEBUG
	if (debug > 2) {
		printf("Received %d bytes from %s:\n", recvc, sptoa(sender));
		pkt_output((struct pkt *)rdata, recvc, stdout);
	}
#endif
	return recvc;
}