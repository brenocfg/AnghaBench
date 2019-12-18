#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_2__ {int ar_event; } ;
struct kaudit_record {TYPE_1__ k_ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  audit_mtx ; 
 int /*<<< orphan*/  audit_pre_q_len ; 
 int /*<<< orphan*/  audit_record_zone ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct kaudit_record* uma_zalloc_arg (int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ) ; 

struct kaudit_record *
audit_new(int event, struct thread *td)
{
	struct kaudit_record *ar;

	/*
	 * Note: the number of outstanding uncommitted audit records is
	 * limited to the number of concurrent threads servicing system calls
	 * in the kernel.
	 */
	ar = uma_zalloc_arg(audit_record_zone, td, M_WAITOK);
	ar->k_ar.ar_event = event;

	mtx_lock(&audit_mtx);
	audit_pre_q_len++;
	mtx_unlock(&audit_mtx);

	return (ar);
}