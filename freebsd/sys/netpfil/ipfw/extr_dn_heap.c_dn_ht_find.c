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
struct dn_ht {int buckets; int (* hash ) (uintptr_t,int,void*) ;void** ht; int ofs; void* (* newh ) (uintptr_t,int,void*) ;int /*<<< orphan*/  entries; scalar_t__ (* match ) (void*,uintptr_t,int,void*) ;} ;

/* Variables and functions */
 int DNHT_INSERT ; 
 int DNHT_MATCH_PTR ; 
 int DNHT_REMOVE ; 
 int stub1 (uintptr_t,int,void*) ; 
 scalar_t__ stub2 (void*,uintptr_t,int,void*) ; 
 void* stub3 (uintptr_t,int,void*) ; 

void *
dn_ht_find(struct dn_ht *ht, uintptr_t key, int flags, void *arg)
{
	int i;
	void **pp, *p;

	if (ht == NULL)	/* easy on an empty hash */
		return NULL;
	i = (ht->buckets == 1) ? 0 :
		(ht->hash(key, flags, arg) & ht->buckets);

	for (pp = &ht->ht[i]; (p = *pp); pp = (void **)((char *)p + ht->ofs)) {
		if (flags & DNHT_MATCH_PTR) {
			if (key == (uintptr_t)p)
				break;
		} else if (ht->match(p, key, flags, arg)) /* found match */
			break;
	}
	if (p) {
		if (flags & DNHT_REMOVE) {
			/* link in the next element */
			*pp = *(void **)((char *)p + ht->ofs);
			*(void **)((char *)p + ht->ofs) = NULL;
			ht->entries--;
		}
	} else if (flags & DNHT_INSERT) {
		// printf("%s before calling new, bucket %d ofs %d\n",
		//	__FUNCTION__, i, ht->ofs);
		p = ht->newh ? ht->newh(key, flags, arg) : (void *)key;
		// printf("%s newh returns %p\n", __FUNCTION__, p);
		if (p) {
			ht->entries++;
			*(void **)((char *)p + ht->ofs) = ht->ht[i];
			ht->ht[i] = p;
		}
	}
	return p;
}