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
struct infra_key {scalar_t__ namelen; int /*<<< orphan*/  zonename; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sockaddr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int 
infra_compfunc(void* key1, void* key2)
{
	struct infra_key* k1 = (struct infra_key*)key1;
	struct infra_key* k2 = (struct infra_key*)key2;
	int r = sockaddr_cmp(&k1->addr, k1->addrlen, &k2->addr, k2->addrlen);
	if(r != 0)
		return r;
	if(k1->namelen != k2->namelen) {
		if(k1->namelen < k2->namelen)
			return -1;
		return 1;
	}
	return query_dname_compare(k1->zonename, k2->zonename);
}