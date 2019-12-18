#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  true_val ;
struct TYPE_8__ {int flags; char* label; } ;
struct pkcs11_slotinfo {int logged_in; int /*<<< orphan*/  session; TYPE_1__ token; } ;
struct pkcs11_key {size_t slotidx; TYPE_6__* provider; int /*<<< orphan*/  keyid_len; int /*<<< orphan*/ * keyid; } ;
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  private_key_class ;
struct TYPE_12__ {struct pkcs11_slotinfo* slotinfo; TYPE_3__* function_list; int /*<<< orphan*/  valid; } ;
struct TYPE_11__ {int member_2; int /*<<< orphan*/  ulValueLen; int /*<<< orphan*/ * pValue; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {char* (* C_Login ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;char* (* C_SignInit ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;char* (* C_Sign ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  char RSA ;
typedef  int CK_ULONG ;
typedef  char* CK_RV ;
typedef  int /*<<< orphan*/  CK_OBJECT_HANDLE ;
typedef  int /*<<< orphan*/  CK_OBJECT_CLASS ;
typedef  TYPE_2__ CK_MECHANISM ;
typedef  TYPE_3__ CK_FUNCTION_LIST ;
typedef  int /*<<< orphan*/  CK_BYTE ;
typedef  int /*<<< orphan*/  CK_BBOOL ;
typedef  TYPE_4__ CK_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  CKA_CLASS ; 
 int /*<<< orphan*/  CKA_ID ; 
 int /*<<< orphan*/  CKA_SIGN ; 
 int CKF_LOGIN_REQUIRED ; 
 int CKF_PROTECTED_AUTHENTICATION_PATH ; 
 int /*<<< orphan*/  CKM_RSA_PKCS ; 
 int /*<<< orphan*/  CKO_PRIVATE_KEY ; 
 char* CKR_OK ; 
 char* CKR_USER_ALREADY_LOGGED_IN ; 
 int /*<<< orphan*/  CKU_USER ; 
 int /*<<< orphan*/  CK_TRUE ; 
 int /*<<< orphan*/  NULL_PTR ; 
 int /*<<< orphan*/  RP_ALLOW_EOF ; 
 struct pkcs11_key* RSA_get_app_data (char*) ; 
 int RSA_size (char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  explicit_bzero (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ pkcs11_find (TYPE_6__*,size_t,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkcs11_interactive ; 
 char* read_passphrase (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* stub2 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  verbose (char*) ; 

__attribute__((used)) static int
pkcs11_rsa_private_encrypt(int flen, const u_char *from, u_char *to, RSA *rsa,
    int padding)
{
	struct pkcs11_key	*k11;
	struct pkcs11_slotinfo	*si;
	CK_FUNCTION_LIST	*f;
	CK_OBJECT_HANDLE	obj;
	CK_ULONG		tlen = 0;
	CK_RV			rv;
	CK_OBJECT_CLASS	private_key_class = CKO_PRIVATE_KEY;
	CK_BBOOL		true_val = CK_TRUE;
	CK_MECHANISM		mech = {
		CKM_RSA_PKCS, NULL_PTR, 0
	};
	CK_ATTRIBUTE		key_filter[] = {
		{CKA_CLASS, NULL, sizeof(private_key_class) },
		{CKA_ID, NULL, 0},
		{CKA_SIGN, NULL, sizeof(true_val) }
	};
	char			*pin = NULL, prompt[1024];
	int			rval = -1;

	key_filter[0].pValue = &private_key_class;
	key_filter[2].pValue = &true_val;

	if ((k11 = RSA_get_app_data(rsa)) == NULL) {
		error("RSA_get_app_data failed for rsa %p", rsa);
		return (-1);
	}
	if (!k11->provider || !k11->provider->valid) {
		error("no pkcs11 (valid) provider for rsa %p", rsa);
		return (-1);
	}
	f = k11->provider->function_list;
	si = &k11->provider->slotinfo[k11->slotidx];
	if ((si->token.flags & CKF_LOGIN_REQUIRED) && !si->logged_in) {
		if (!pkcs11_interactive) {
			error("need pin entry%s", (si->token.flags &
			    CKF_PROTECTED_AUTHENTICATION_PATH) ?
			    " on reader keypad" : "");
			return (-1);
		}
		if (si->token.flags & CKF_PROTECTED_AUTHENTICATION_PATH)
			verbose("Deferring PIN entry to reader keypad.");
		else {
			snprintf(prompt, sizeof(prompt),
			    "Enter PIN for '%s': ", si->token.label);
			pin = read_passphrase(prompt, RP_ALLOW_EOF);
			if (pin == NULL)
				return (-1);	/* bail out */
		}
		rv = f->C_Login(si->session, CKU_USER, (u_char *)pin,
		    (pin != NULL) ? strlen(pin) : 0);
		if (pin != NULL) {
			explicit_bzero(pin, strlen(pin));
			free(pin);
		}
		if (rv != CKR_OK && rv != CKR_USER_ALREADY_LOGGED_IN) {
			error("C_Login failed: %lu", rv);
			return (-1);
		}
		si->logged_in = 1;
	}
	key_filter[1].pValue = k11->keyid;
	key_filter[1].ulValueLen = k11->keyid_len;
	/* try to find object w/CKA_SIGN first, retry w/o */
	if (pkcs11_find(k11->provider, k11->slotidx, key_filter, 3, &obj) < 0 &&
	    pkcs11_find(k11->provider, k11->slotidx, key_filter, 2, &obj) < 0) {
		error("cannot find private key");
	} else if ((rv = f->C_SignInit(si->session, &mech, obj)) != CKR_OK) {
		error("C_SignInit failed: %lu", rv);
	} else {
		/* XXX handle CKR_BUFFER_TOO_SMALL */
		tlen = RSA_size(rsa);
		rv = f->C_Sign(si->session, (CK_BYTE *)from, flen, to, &tlen);
		if (rv == CKR_OK) 
			rval = tlen;
		else 
			error("C_Sign failed: %lu", rv);
	}
	return (rval);
}