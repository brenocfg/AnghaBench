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
struct an_req {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_ltv_key {int kindex; int klen; int* mac; } ;
typedef  int /*<<< orphan*/  areq ;

/* Variables and functions */
 int /*<<< orphan*/  AN_RID_WEP_PERM ; 
 int /*<<< orphan*/  AN_RID_WEP_TEMP ; 
 int /*<<< orphan*/  an_setval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  an_str2key (char const*,struct an_ltv_key*) ; 
 int /*<<< orphan*/  bzero (struct an_req*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
an_setkeys(const char *iface, const char *key, int keytype)
{
	struct an_req		areq;
	struct an_ltv_key	*k;

	bzero(&areq, sizeof(areq));
	k = (struct an_ltv_key *)&areq;

	if (strlen(key) > 28) {
		err(1, "encryption key must be no "
		    "more than 18 characters long");
	}

	an_str2key(key, k);
	
	k->kindex=keytype/2;

	if (!(k->klen==0 || k->klen==5 || k->klen==13)) {
		err(1, "encryption key must be 0, 5 or 13 bytes long");
	}

	/* default mac and only valid one (from manual) 1.0.0.0.0.0 */
	k->mac[0]=1;
	k->mac[1]=0;
	k->mac[2]=0;
	k->mac[3]=0;
	k->mac[4]=0;
	k->mac[5]=0;

	switch(keytype & 1) {
	case 0:
	  areq.an_len = sizeof(struct an_ltv_key);
	  areq.an_type = AN_RID_WEP_PERM;
	  an_setval(iface, &areq);
	  break;
	case 1:
	  areq.an_len = sizeof(struct an_ltv_key);
	  areq.an_type = AN_RID_WEP_TEMP;
	  an_setval(iface, &areq);
	  break;
	}
}