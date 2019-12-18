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
struct ip6_moptions {int /*<<< orphan*/  im6o_head; int /*<<< orphan*/  im6o_multicast_loop; int /*<<< orphan*/  im6o_multicast_hlim; int /*<<< orphan*/ * im6o_multicast_ifp; } ;
struct inpcb {struct ip6_moptions* in6p_moptions; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  M_IP6MOPTS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ip6_defmcasthlim ; 
 int /*<<< orphan*/  free (struct ip6_moptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_mcast_loop ; 
 struct ip6_moptions* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ip6_moptions *
in6p_findmoptions(struct inpcb *inp)
{
	struct ip6_moptions	 *imo;

	INP_WLOCK(inp);
	if (inp->in6p_moptions != NULL)
		return (inp->in6p_moptions);

	INP_WUNLOCK(inp);

	imo = malloc(sizeof(*imo), M_IP6MOPTS, M_WAITOK);

	imo->im6o_multicast_ifp = NULL;
	imo->im6o_multicast_hlim = V_ip6_defmcasthlim;
	imo->im6o_multicast_loop = in6_mcast_loop;
	STAILQ_INIT(&imo->im6o_head);

	INP_WLOCK(inp);
	if (inp->in6p_moptions != NULL) {
		free(imo, M_IP6MOPTS);
		return (inp->in6p_moptions);
	}
	inp->in6p_moptions = imo;
	return (imo);
}