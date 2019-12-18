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
struct ub_ctx {int dummy; } ;

/* Variables and functions */
 int LDNS_RR_TYPE_A ; 
 int LDNS_RR_TYPE_AAAA ; 
 int LDNS_RR_TYPE_MX ; 
 int /*<<< orphan*/  dnslook (struct ub_ctx*,char*,int,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int massage_class (char const*) ; 
 char* massage_qname (char const*,int*) ; 
 int massage_type (char const*,int,int*) ; 
 int /*<<< orphan*/  ub_ctx_delete (struct ub_ctx*) ; 

__attribute__((used)) static void
lookup(struct ub_ctx* ctx, const char* nm, const char* qt, const char* qc)
{
	/* massage input into a query name, type and class */
	int multi = 0;	 /* no type, so do A, AAAA, MX */
	int reverse = 0; /* we are doing a reverse lookup */
	char* realq = massage_qname(nm, &reverse);
	int t = massage_type(qt, reverse, &multi);
	int c = massage_class(qc);

	/* perform the query */
	if(multi) {
		if(!dnslook(ctx, realq, LDNS_RR_TYPE_A, c, 1)) {
			/* domain exists, lookup more */
			(void)dnslook(ctx, realq, LDNS_RR_TYPE_AAAA, c, 0);
			(void)dnslook(ctx, realq, LDNS_RR_TYPE_MX, c, 0);
		}
	} else {
		(void)dnslook(ctx, realq, t, c, 1);
	}
	ub_ctx_delete(ctx);
	free(realq);
}