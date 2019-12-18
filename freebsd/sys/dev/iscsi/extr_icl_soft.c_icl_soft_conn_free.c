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
struct kobj {int dummy; } ;
struct icl_conn {scalar_t__ ic_outstanding_pdus; int /*<<< orphan*/  ic_receive_cv; int /*<<< orphan*/  ic_send_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_ICL_SOFT ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_ncons ; 
 int /*<<< orphan*/  kobj_delete (struct kobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 

void
icl_soft_conn_free(struct icl_conn *ic)
{

#ifdef DIAGNOSTIC
	KASSERT(ic->ic_outstanding_pdus == 0,
	    ("destroying session with %d outstanding PDUs",
	     ic->ic_outstanding_pdus));
#endif
	cv_destroy(&ic->ic_send_cv);
	cv_destroy(&ic->ic_receive_cv);
	kobj_delete((struct kobj *)ic, M_ICL_SOFT);
	refcount_release(&icl_ncons);
}