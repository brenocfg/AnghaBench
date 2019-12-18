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
typedef  scalar_t__ time_t ;
struct packed_rrset_data {scalar_t__ security; scalar_t__ trust; scalar_t__ ttl; size_t count; size_t rrsig_count; scalar_t__* rr_ttl; } ;

/* Variables and functions */
 scalar_t__ sec_status_bogus ; 
 scalar_t__ sec_status_secure ; 

__attribute__((used)) static int
need_to_update_rrset(void* nd, void* cd, time_t timenow, int equal, int ns)
{
	struct packed_rrset_data* newd = (struct packed_rrset_data*)nd;
	struct packed_rrset_data* cached = (struct packed_rrset_data*)cd;
	/* 	o store if rrset has been validated 
	 *  		everything better than bogus data 
	 *  		secure is preferred */
	if( newd->security == sec_status_secure &&
		cached->security != sec_status_secure)
		return 1;
	if( cached->security == sec_status_bogus && 
		newd->security != sec_status_bogus && !equal)
		return 1;
        /*      o if current RRset is more trustworthy - insert it */
        if( newd->trust > cached->trust ) {
		/* if the cached rrset is bogus, and this one equal,
		 * do not update the TTL - let it expire. */
		if(equal && cached->ttl >= timenow && 
			cached->security == sec_status_bogus)
			return 0;
                return 1;
	}
	/*	o item in cache has expired */
	if( cached->ttl < timenow )
		return 1;
	/*  o same trust, but different in data - insert it */
	if( newd->trust == cached->trust && !equal ) {
		/* if this is type NS, do not 'stick' to owner that changes
		 * the NS RRset, but use the old TTL for the new data, and
		 * update to fetch the latest data. ttl is not expired, because
		 * that check was before this one. */
		if(ns) {
			size_t i;
			newd->ttl = cached->ttl;
			for(i=0; i<(newd->count+newd->rrsig_count); i++)
				if(newd->rr_ttl[i] > newd->ttl)
					newd->rr_ttl[i] = newd->ttl;
		}
		return 1;
	}
	return 0;
}