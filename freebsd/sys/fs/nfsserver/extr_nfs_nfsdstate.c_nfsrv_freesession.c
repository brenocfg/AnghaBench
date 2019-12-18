#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct nfssessionhash {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * nfsess_xprt; } ;
struct nfsdsession {scalar_t__ sess_refcnt; TYPE_2__ sess_cbsess; TYPE_1__* sess_slots; int /*<<< orphan*/ * sess_sessionid; } ;
struct TYPE_3__ {int /*<<< orphan*/ * nfssl_reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfsdsession*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSDSESSION ; 
 int NFSERR_BACKCHANBUSY ; 
 int NFSERR_BADSESSION ; 
 int /*<<< orphan*/  NFSLOCKSESSION (struct nfssessionhash*) ; 
 int /*<<< orphan*/  NFSLOCKSTATE () ; 
 struct nfssessionhash* NFSSESSIONHASH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSUNLOCKSESSION (struct nfssessionhash*) ; 
 int /*<<< orphan*/  NFSUNLOCKSTATE () ; 
 int NFSV4_SLOTS ; 
 int /*<<< orphan*/  SVC_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct nfsdsession*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 struct nfsdsession* nfsrv_findsession (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sess_hash ; 
 int /*<<< orphan*/  sess_list ; 

__attribute__((used)) static int
nfsrv_freesession(struct nfsdsession *sep, uint8_t *sessionid)
{
	struct nfssessionhash *shp;
	int i;

	NFSLOCKSTATE();
	if (sep == NULL) {
		shp = NFSSESSIONHASH(sessionid);
		NFSLOCKSESSION(shp);
		sep = nfsrv_findsession(sessionid);
	} else {
		shp = NFSSESSIONHASH(sep->sess_sessionid);
		NFSLOCKSESSION(shp);
	}
	if (sep != NULL) {
		sep->sess_refcnt--;
		if (sep->sess_refcnt > 0) {
			NFSUNLOCKSESSION(shp);
			NFSUNLOCKSTATE();
			return (NFSERR_BACKCHANBUSY);
		}
		LIST_REMOVE(sep, sess_hash);
		LIST_REMOVE(sep, sess_list);
	}
	NFSUNLOCKSESSION(shp);
	NFSUNLOCKSTATE();
	if (sep == NULL)
		return (NFSERR_BADSESSION);
	for (i = 0; i < NFSV4_SLOTS; i++)
		if (sep->sess_slots[i].nfssl_reply != NULL)
			m_freem(sep->sess_slots[i].nfssl_reply);
	if (sep->sess_cbsess.nfsess_xprt != NULL)
		SVC_RELEASE(sep->sess_cbsess.nfsess_xprt);
	free(sep, M_NFSDSESSION);
	return (0);
}