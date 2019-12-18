#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_object {int num_attributes; TYPE_2__* attrs; } ;
struct session_state {int dummy; } ;
struct TYPE_7__ {scalar_t__ type; size_t ulValueLen; scalar_t__ pValue; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ ulValueLen; int /*<<< orphan*/  pValue; } ;
struct TYPE_6__ {scalar_t__ secret; TYPE_1__ attribute; } ;
typedef  size_t CK_ULONG ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  int /*<<< orphan*/  CK_RV ;
typedef  int /*<<< orphan*/  CK_OBJECT_HANDLE ;
typedef  TYPE_3__* CK_ATTRIBUTE_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_OK ; 
 scalar_t__ HANDLE_OBJECT_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 scalar_t__ NULL_PTR ; 
 int /*<<< orphan*/  VERIFY_SESSION_HANDLE (int /*<<< orphan*/ ,struct session_state**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  object_handle_to_object (int /*<<< orphan*/ ,struct st_object**) ; 
 int /*<<< orphan*/  st_logf (char*,unsigned long) ; 

CK_RV
C_GetAttributeValue(CK_SESSION_HANDLE hSession,
		    CK_OBJECT_HANDLE hObject,
		    CK_ATTRIBUTE_PTR pTemplate,
		    CK_ULONG ulCount)
{
    struct session_state *state;
    struct st_object *obj;
    CK_ULONG i;
    CK_RV ret;
    int j;

    INIT_CONTEXT();

    st_logf("GetAttributeValue: %lx\n",
	    (unsigned long)HANDLE_OBJECT_ID(hObject));
    VERIFY_SESSION_HANDLE(hSession, &state);

    if ((ret = object_handle_to_object(hObject, &obj)) != CKR_OK) {
	st_logf("object not found: %lx\n",
		(unsigned long)HANDLE_OBJECT_ID(hObject));
	return ret;
    }

    for (i = 0; i < ulCount; i++) {
	st_logf("	getting 0x%08lx\n", (unsigned long)pTemplate[i].type);
	for (j = 0; j < obj->num_attributes; j++) {
	    if (obj->attrs[j].secret) {
		pTemplate[i].ulValueLen = (CK_ULONG)-1;
		break;
	    }
	    if (pTemplate[i].type == obj->attrs[j].attribute.type) {
		if (pTemplate[i].pValue != NULL_PTR && obj->attrs[j].secret == 0) {
		    if (pTemplate[i].ulValueLen >= obj->attrs[j].attribute.ulValueLen)
			memcpy(pTemplate[i].pValue, obj->attrs[j].attribute.pValue,
			       obj->attrs[j].attribute.ulValueLen);
		}
		pTemplate[i].ulValueLen = obj->attrs[j].attribute.ulValueLen;
		break;
	    }
	}
	if (j == obj->num_attributes) {
	    st_logf("key type: 0x%08lx not found\n", (unsigned long)pTemplate[i].type);
	    pTemplate[i].ulValueLen = (CK_ULONG)-1;
	}

    }
    return CKR_OK;
}