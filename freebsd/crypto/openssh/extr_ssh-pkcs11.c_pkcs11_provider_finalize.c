#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pkcs11_provider {size_t nslots; int /*<<< orphan*/  handle; TYPE_2__* function_list; scalar_t__ valid; TYPE_1__* slotinfo; int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* C_Finalize ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* C_CloseSession ) (scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__ session; } ;
typedef  size_t CK_ULONG ;
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_OK ; 
 int /*<<< orphan*/  debug (char*,struct pkcs11_provider*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dlclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pkcs11_provider_finalize(struct pkcs11_provider *p)
{
	CK_RV rv;
	CK_ULONG i;

	debug("pkcs11_provider_finalize: %p refcount %d valid %d",
	    p, p->refcount, p->valid);
	if (!p->valid)
		return;
	for (i = 0; i < p->nslots; i++) {
		if (p->slotinfo[i].session &&
		    (rv = p->function_list->C_CloseSession(
		    p->slotinfo[i].session)) != CKR_OK)
			error("C_CloseSession failed: %lu", rv);
	}
	if ((rv = p->function_list->C_Finalize(NULL)) != CKR_OK)
		error("C_Finalize failed: %lu", rv);
	p->valid = 0;
	p->function_list = NULL;
	dlclose(p->handle);
}