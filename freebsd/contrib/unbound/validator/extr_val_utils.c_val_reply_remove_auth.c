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
struct ub_packed_rrset_key {int dummy; } ;
struct reply_info {size_t rrset_count; size_t an_numrrsets; size_t ns_numrrsets; scalar_t__ rrsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

void val_reply_remove_auth(struct reply_info* rep, size_t index)
{
	log_assert(index < rep->rrset_count);
	log_assert(index >= rep->an_numrrsets);
	log_assert(index < rep->an_numrrsets+rep->ns_numrrsets);
	memmove(rep->rrsets+index, rep->rrsets+index+1,
		sizeof(struct ub_packed_rrset_key*)*
		(rep->rrset_count - index - 1));
	rep->ns_numrrsets--;
	rep->rrset_count--;
}