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
struct protosw {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int EPFNOSUPPORT ; 
 int EPROTONOSUPPORT ; 
 short IPPROTO_MAX ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 struct protosw* inetsw ; 
 int* ip_protox ; 
 struct protosw* pffindproto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ipproto_unregister(short ipproto)
{
	struct protosw *pr;

	/* Sanity checks. */
	if (ipproto <= 0 || ipproto >= IPPROTO_MAX)
		return (EPROTONOSUPPORT);

	/* Check if the protocol was indeed registered. */
	pr = pffindproto(PF_INET, IPPROTO_RAW, SOCK_RAW);
	if (pr == NULL)
		return (EPFNOSUPPORT);
	if (ip_protox[ipproto] == pr - inetsw)  /* IPPROTO_RAW */
		return (ENOENT);

	/* Reset the protocol slot to IPPROTO_RAW. */
	ip_protox[ipproto] = pr - inetsw;
	return (0);
}