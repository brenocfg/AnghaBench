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
struct enamemem {int e_addr0; int e_addr1; int e_addr2; struct enamemem* e_nxt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ndo_error ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int HASHNAMESIZE ; 
 scalar_t__ calloc (int,int) ; 
 struct enamemem* enametable ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 

__attribute__((used)) static inline struct enamemem *
lookup_emem(netdissect_options *ndo, const u_char *ep)
{
	register u_int i, j, k;
	struct enamemem *tp;

	k = (ep[0] << 8) | ep[1];
	j = (ep[2] << 8) | ep[3];
	i = (ep[4] << 8) | ep[5];

	tp = &enametable[(i ^ j) & (HASHNAMESIZE-1)];
	while (tp->e_nxt)
		if (tp->e_addr0 == i &&
		    tp->e_addr1 == j &&
		    tp->e_addr2 == k)
			return tp;
		else
			tp = tp->e_nxt;
	tp->e_addr0 = i;
	tp->e_addr1 = j;
	tp->e_addr2 = k;
	tp->e_nxt = (struct enamemem *)calloc(1, sizeof(*tp));
	if (tp->e_nxt == NULL)
		(*ndo->ndo_error)(ndo, "lookup_emem: calloc");

	return tp;
}