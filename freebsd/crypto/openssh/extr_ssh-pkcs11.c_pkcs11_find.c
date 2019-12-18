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
struct pkcs11_provider {TYPE_1__* slotinfo; TYPE_2__* function_list; } ;
struct TYPE_4__ {char* (* C_FindObjectsInit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ;char* (* C_FindObjects ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t*) ;char* (* C_FindObjectsFinal ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  session; } ;
typedef  size_t CK_ULONG ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  char* CK_RV ;
typedef  int /*<<< orphan*/  CK_OBJECT_HANDLE ;
typedef  TYPE_2__ CK_FUNCTION_LIST ;
typedef  int /*<<< orphan*/  CK_ATTRIBUTE ;

/* Variables and functions */
 char* CKR_OK ; 
 int /*<<< orphan*/  debug (char*,size_t,size_t,char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 char* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 char* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t*) ; 
 char* stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pkcs11_find(struct pkcs11_provider *p, CK_ULONG slotidx, CK_ATTRIBUTE *attr,
    CK_ULONG nattr, CK_OBJECT_HANDLE *obj)
{
	CK_FUNCTION_LIST	*f;
	CK_SESSION_HANDLE	session;
	CK_ULONG		nfound = 0;
	CK_RV			rv;
	int			ret = -1;

	f = p->function_list;
	session = p->slotinfo[slotidx].session;
	if ((rv = f->C_FindObjectsInit(session, attr, nattr)) != CKR_OK) {
		error("C_FindObjectsInit failed (nattr %lu): %lu", nattr, rv);
		return (-1);
	}
	if ((rv = f->C_FindObjects(session, obj, 1, &nfound)) != CKR_OK ||
	    nfound != 1) {
		debug("C_FindObjects failed (nfound %lu nattr %lu): %lu",
		    nfound, nattr, rv);
	} else
		ret = 0;
	if ((rv = f->C_FindObjectsFinal(session)) != CKR_OK)
		error("C_FindObjectsFinal failed: %lu", rv);
	return (ret);
}