#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_len; } ;
struct TYPE_12__ {int sa_len; int /*<<< orphan*/  sa_family; } ;
struct TYPE_13__ {TYPE_5__ sa; } ;
struct TYPE_10__ {int sa_len; int /*<<< orphan*/  sa_family; } ;
struct TYPE_11__ {TYPE_3__ sa; } ;
struct TYPE_14__ {TYPE_6__ dst; TYPE_4__ src; int /*<<< orphan*/  ul_proto; int /*<<< orphan*/  dir; } ;
struct secpolicy {TYPE_7__ spidx; int /*<<< orphan*/  priority; int /*<<< orphan*/  created; int /*<<< orphan*/  tcount; struct ipsecrequest** req; int /*<<< orphan*/  state; int /*<<< orphan*/  policy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; int /*<<< orphan*/  proto; } ;
struct ipsecrequest {TYPE_2__ saidx; int /*<<< orphan*/  level; } ;
struct ipsec_softc {TYPE_1__* ifp; } ;
struct TYPE_8__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IPPROTO_ESP ; 
 int /*<<< orphan*/  IPSEC_DIR_INBOUND ; 
 int /*<<< orphan*/  IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  IPSEC_LEVEL_UNIQUE ; 
 int /*<<< orphan*/  IPSEC_MODE_TUNNEL ; 
 int /*<<< orphan*/  IPSEC_POLICY_IPSEC ; 
 int IPSEC_SPCOUNT ; 
 int /*<<< orphan*/  IPSEC_SPSTATE_DEAD ; 
 int /*<<< orphan*/  IPSEC_ULPROTO_ANY ; 
 int /*<<< orphan*/  bcopy (struct sockaddr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ipsecrequest* ipsec_newisr () ; 
 int /*<<< orphan*/  key_freesp (struct secpolicy**) ; 
 struct secpolicy* key_newsp () ; 
 int /*<<< orphan*/  memset (struct secpolicy**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time_second ; 

__attribute__((used)) static int
ipsec_newpolicies(struct ipsec_softc *sc, struct secpolicy *sp[IPSEC_SPCOUNT],
    const struct sockaddr *src, const struct sockaddr *dst, uint32_t reqid)
{
	struct ipsecrequest *isr;
	int i;

	memset(sp, 0, sizeof(struct secpolicy *) * IPSEC_SPCOUNT);
	for (i = 0; i < IPSEC_SPCOUNT; i++) {
		if ((sp[i] = key_newsp()) == NULL)
			goto fail;
		if ((isr = ipsec_newisr()) == NULL)
			goto fail;

		sp[i]->policy = IPSEC_POLICY_IPSEC;
		sp[i]->state = IPSEC_SPSTATE_DEAD;
		sp[i]->req[sp[i]->tcount++] = isr;
		sp[i]->created = time_second;
		/* Use priority field to store if_index */
		sp[i]->priority = sc->ifp->if_index;
		isr->level = IPSEC_LEVEL_UNIQUE;
		isr->saidx.proto = IPPROTO_ESP;
		isr->saidx.mode = IPSEC_MODE_TUNNEL;
		isr->saidx.reqid = reqid;
		if (i % 2 == 0) {
			sp[i]->spidx.dir = IPSEC_DIR_INBOUND;
			bcopy(src, &isr->saidx.dst, src->sa_len);
			bcopy(dst, &isr->saidx.src, dst->sa_len);
		} else {
			sp[i]->spidx.dir = IPSEC_DIR_OUTBOUND;
			bcopy(src, &isr->saidx.src, src->sa_len);
			bcopy(dst, &isr->saidx.dst, dst->sa_len);
		}
		sp[i]->spidx.ul_proto = IPSEC_ULPROTO_ANY;
#ifdef INET
		if (i < 2) {
			sp[i]->spidx.src.sa.sa_family =
			    sp[i]->spidx.dst.sa.sa_family = AF_INET;
			sp[i]->spidx.src.sa.sa_len =
			    sp[i]->spidx.dst.sa.sa_len =
			    sizeof(struct sockaddr_in);
			continue;
		}
#endif
#ifdef INET6
		sp[i]->spidx.src.sa.sa_family =
		    sp[i]->spidx.dst.sa.sa_family = AF_INET6;
		sp[i]->spidx.src.sa.sa_len =
		    sp[i]->spidx.dst.sa.sa_len = sizeof(struct sockaddr_in6);
#endif
	}
	return (0);
fail:
	for (i = 0; i < IPSEC_SPCOUNT; i++)
		key_freesp(&sp[i]);
	return (ENOMEM);
}