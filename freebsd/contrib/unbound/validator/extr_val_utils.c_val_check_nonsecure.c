#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ub_packed_rrset_key {int dummy; } ;
struct reply_info {size_t an_numrrsets; size_t ns_numrrsets; size_t rrset_count; scalar_t__ ar_numrrsets; TYPE_4__** rrsets; int /*<<< orphan*/  security; } ;
struct packed_rrset_data {scalar_t__ security; } ;
struct module_env {TYPE_2__* cfg; } ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/  dname; } ;
struct TYPE_9__ {TYPE_3__ entry; TYPE_1__ rk; } ;
struct TYPE_7__ {int /*<<< orphan*/  val_clean_additional; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memmove (TYPE_4__**,TYPE_4__**,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_status_bogus ; 
 scalar_t__ sec_status_secure ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void
val_check_nonsecure(struct module_env* env, struct reply_info* rep) 
{
	size_t i;
	/* authority */
	for(i=rep->an_numrrsets; i<rep->an_numrrsets+rep->ns_numrrsets; i++) {
		if(((struct packed_rrset_data*)rep->rrsets[i]->entry.data)
			->security != sec_status_secure) {
			/* because we want to return the authentic original
			 * message when presented with CD-flagged queries,
			 * we need to preserve AUTHORITY section data.
			 * However, this rrset is not signed or signed
			 * with the wrong keys. Validation has tried to
			 * verify this rrset with the keysets of import.
			 * But this rrset did not verify.
			 * Therefore the message is bogus.
			 */

			/* check if authority has an NS record
			 * which is bad, and there is an answer section with
			 * data.  In that case, delete NS and additional to 
			 * be lenient and make a minimal response */
			if(rep->an_numrrsets != 0 &&
				ntohs(rep->rrsets[i]->rk.type) 
				== LDNS_RR_TYPE_NS) {
				verbose(VERB_ALGO, "truncate to minimal");
				rep->ar_numrrsets = 0;
				rep->rrset_count = rep->an_numrrsets +
					rep->ns_numrrsets;
				/* remove this unneeded authority rrset */
				memmove(rep->rrsets+i, rep->rrsets+i+1, 
					sizeof(struct ub_packed_rrset_key*)*
					(rep->rrset_count - i - 1));
				rep->ns_numrrsets--;
				rep->rrset_count--;
				i--;
				return;
			}

			log_nametypeclass(VERB_QUERY, "message is bogus, "
				"non secure rrset",
				rep->rrsets[i]->rk.dname, 
				ntohs(rep->rrsets[i]->rk.type),
				ntohs(rep->rrsets[i]->rk.rrset_class));
			rep->security = sec_status_bogus;
			return;
		}
	}
	/* additional */
	if(!env->cfg->val_clean_additional)
		return;
	for(i=rep->an_numrrsets+rep->ns_numrrsets; i<rep->rrset_count; i++) {
		if(((struct packed_rrset_data*)rep->rrsets[i]->entry.data)
			->security != sec_status_secure) {
			/* This does not cause message invalidation. It was
			 * simply unsigned data in the additional. The
			 * RRSIG must have been truncated off the message.
			 *
			 * However, we do not want to return possible bogus
			 * data to clients that rely on this service for
			 * their authentication.
			 */
			/* remove this unneeded additional rrset */
			memmove(rep->rrsets+i, rep->rrsets+i+1, 
				sizeof(struct ub_packed_rrset_key*)*
				(rep->rrset_count - i - 1));
			rep->ar_numrrsets--;
			rep->rrset_count--;
			i--;
		}
	}
}