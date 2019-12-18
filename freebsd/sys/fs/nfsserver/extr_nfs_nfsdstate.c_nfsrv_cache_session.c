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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nfssessionhash {int dummy; } ;
struct nfsdsession {int /*<<< orphan*/  sess_slots; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSLOCKSESSION (struct nfssessionhash*) ; 
 struct nfssessionhash* NFSSESSIONHASH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSUNLOCKSESSION (struct nfssessionhash*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct nfsdsession* nfsrv_findsession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_seqsess_cacherep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct mbuf**) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
nfsrv_cache_session(uint8_t *sessionid, uint32_t slotid, int repstat,
   struct mbuf **m)
{
	struct nfsdsession *sep;
	struct nfssessionhash *shp;

	shp = NFSSESSIONHASH(sessionid);
	NFSLOCKSESSION(shp);
	sep = nfsrv_findsession(sessionid);
	if (sep == NULL) {
		NFSUNLOCKSESSION(shp);
		printf("nfsrv_cache_session: no session\n");
		m_freem(*m);
		return;
	}
	nfsv4_seqsess_cacherep(slotid, sep->sess_slots, repstat, m);
	NFSUNLOCKSESSION(shp);
}