#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_object {int dummy; } ;
struct session_state {int /*<<< orphan*/  sign_object; int /*<<< orphan*/  sign_mechanism; } ;
typedef  int /*<<< orphan*/  mechs ;
typedef  int /*<<< orphan*/  bool_true ;
typedef  int /*<<< orphan*/  attr ;
struct TYPE_3__ {int member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  scalar_t__ CK_RV ;
typedef  int /*<<< orphan*/  CK_OBJECT_HANDLE ;
typedef  int /*<<< orphan*/  CK_MECHANISM_TYPE ;
typedef  int /*<<< orphan*/  CK_MECHANISM_PTR ;
typedef  int /*<<< orphan*/  CK_BBOOL ;
typedef  TYPE_1__ CK_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  CKA_SIGN ; 
 int /*<<< orphan*/  CKM_RSA_PKCS ; 
 scalar_t__ CKR_OK ; 
 int /*<<< orphan*/  CK_TRUE ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  OBJECT_ID (struct st_object*) ; 
 int /*<<< orphan*/  VERIFY_SESSION_HANDLE (int /*<<< orphan*/ ,struct session_state**) ; 
 scalar_t__ commonInit (TYPE_1__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct st_object**) ; 
 scalar_t__ dup_mechanism (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_logf (char*) ; 

CK_RV
C_SignInit(CK_SESSION_HANDLE hSession,
	   CK_MECHANISM_PTR pMechanism,
	   CK_OBJECT_HANDLE hKey)
{
    struct session_state *state;
    CK_MECHANISM_TYPE mechs[] = { CKM_RSA_PKCS };
    CK_BBOOL bool_true = CK_TRUE;
    CK_ATTRIBUTE attr[] = {
	{ CKA_SIGN, &bool_true, sizeof(bool_true) }
    };
    struct st_object *o;
    CK_RV ret;

    INIT_CONTEXT();
    st_logf("SignInit\n");
    VERIFY_SESSION_HANDLE(hSession, &state);

    ret = commonInit(attr, sizeof(attr)/sizeof(attr[0]),
		     mechs, sizeof(mechs)/sizeof(mechs[0]),
		     pMechanism, hKey, &o);
    if (ret)
	return ret;

    ret = dup_mechanism(&state->sign_mechanism, pMechanism);
    if (ret == CKR_OK)
	state->sign_object = OBJECT_ID(o);

    return CKR_OK;
}