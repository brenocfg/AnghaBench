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
typedef  int u_int ;
typedef  int u_char ;
struct protoidmem {int p_oui; int p_proto; struct protoidmem* p_nxt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int HASHNAMESIZE ; 
 scalar_t__ calloc (int,int) ; 
 struct protoidmem* protoidtable ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

__attribute__((used)) static inline struct protoidmem *
lookup_protoid(netdissect_options *ndo, const u_char *pi)
{
	register u_int i, j;
	struct protoidmem *tp;

	/* 5 octets won't be aligned */
	i = (((pi[0] << 8) + pi[1]) << 8) + pi[2];
	j =   (pi[3] << 8) + pi[4];
	/* XXX should be endian-insensitive, but do big-endian testing  XXX */

	tp = &protoidtable[(i ^ j) & (HASHNAMESIZE-1)];
	while (tp->p_nxt)
		if (tp->p_oui == i && tp->p_proto == j)
			return tp;
		else
			tp = tp->p_nxt;
	tp->p_oui = i;
	tp->p_proto = j;
	tp->p_nxt = (struct protoidmem *)calloc(1, sizeof(*tp));
	if (tp->p_nxt == NULL)
		(*ndo->ndo_error)(ndo, "lookup_protoid: calloc");

	return tp;
}