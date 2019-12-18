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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct ip_moptions {int imo_multicast_vif; int /*<<< orphan*/  imo_head; int /*<<< orphan*/  imo_multicast_loop; int /*<<< orphan*/  imo_multicast_ttl; TYPE_1__ imo_multicast_addr; int /*<<< orphan*/ * imo_multicast_ifp; } ;
struct inpcb {struct ip_moptions* inp_moptions; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  IP_DEFAULT_MULTICAST_TTL ; 
 int /*<<< orphan*/  M_IPMOPTS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ip_moptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_mcast_loop ; 
 struct ip_moptions* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ip_moptions *
inp_findmoptions(struct inpcb *inp)
{
	struct ip_moptions	 *imo;

	INP_WLOCK(inp);
	if (inp->inp_moptions != NULL)
		return (inp->inp_moptions);

	INP_WUNLOCK(inp);

	imo = malloc(sizeof(*imo), M_IPMOPTS, M_WAITOK);

	imo->imo_multicast_ifp = NULL;
	imo->imo_multicast_addr.s_addr = INADDR_ANY;
	imo->imo_multicast_vif = -1;
	imo->imo_multicast_ttl = IP_DEFAULT_MULTICAST_TTL;
	imo->imo_multicast_loop = in_mcast_loop;
	STAILQ_INIT(&imo->imo_head);

	INP_WLOCK(inp);
	if (inp->inp_moptions != NULL) {
		free(imo, M_IPMOPTS);
		return (inp->inp_moptions);
	}
	inp->inp_moptions = imo;
	return (imo);
}