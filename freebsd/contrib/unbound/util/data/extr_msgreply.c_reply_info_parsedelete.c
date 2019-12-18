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
struct reply_info {size_t rrset_count; int /*<<< orphan*/ * rrsets; } ;
struct alloc_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct reply_info*) ; 
 int /*<<< orphan*/  ub_packed_rrset_parsedelete (int /*<<< orphan*/ ,struct alloc_cache*) ; 

void 
reply_info_parsedelete(struct reply_info* rep, struct alloc_cache* alloc)
{
	size_t i;
	if(!rep) 
		return;
	/* no need to lock, since not shared in hashtables. */
	for(i=0; i<rep->rrset_count; i++) {
		ub_packed_rrset_parsedelete(rep->rrsets[i], alloc);
	}
	free(rep);
}