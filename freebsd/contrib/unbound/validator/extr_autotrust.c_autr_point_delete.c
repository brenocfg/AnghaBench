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
struct trust_anchor {struct trust_anchor* name; struct trust_anchor* autr; struct trust_anchor* file; struct trust_anchor* rr; struct trust_anchor* next; struct trust_anchor* keys; int /*<<< orphan*/  dnskey_rrset; int /*<<< orphan*/  ds_rrset; int /*<<< orphan*/  lock; } ;
struct autr_ta {struct autr_ta* name; struct autr_ta* autr; struct autr_ta* file; struct autr_ta* rr; struct autr_ta* next; struct autr_ta* keys; int /*<<< orphan*/  dnskey_rrset; int /*<<< orphan*/  ds_rrset; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  autr_rrset_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct trust_anchor*) ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_unprotect (int /*<<< orphan*/ *,struct trust_anchor*) ; 

void autr_point_delete(struct trust_anchor* tp)
{
	if(!tp)
		return;
	lock_unprotect(&tp->lock, tp);
	lock_unprotect(&tp->lock, tp->autr);
	lock_basic_destroy(&tp->lock);
	autr_rrset_delete(tp->ds_rrset);
	autr_rrset_delete(tp->dnskey_rrset);
	if(tp->autr) {
		struct autr_ta* p = tp->autr->keys, *np;
		while(p) {
			np = p->next;
			free(p->rr);
			free(p);
			p = np;
		}
		free(tp->autr->file);
		free(tp->autr);
	}
	free(tp->name);
	free(tp);
}