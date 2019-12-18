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
struct secpolicyindex {int dummy; } ;
struct spdcache_entry {struct secpolicy* sp; struct secpolicyindex spidx; } ;
struct secpolicy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPSEC_SPDCACHE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SP_ADDREF (struct secpolicy*) ; 
 struct spdcache_entry* malloc (int,int /*<<< orphan*/ ,int) ; 

struct spdcache_entry *
spdcache_entry_alloc(const struct secpolicyindex *spidx, struct secpolicy *sp)
{
	struct spdcache_entry *entry;

	entry = malloc(sizeof(struct spdcache_entry),
		    M_IPSEC_SPDCACHE, M_NOWAIT|M_ZERO);
	if (entry == NULL)
		return NULL;

	if (sp != NULL)
		SP_ADDREF(sp);

	entry->spidx = *spidx;
	entry->sp = sp;

	return (entry);
}