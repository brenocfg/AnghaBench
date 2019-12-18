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
struct TYPE_3__ {int login_done; } ;
struct TYPE_4__ {TYPE_1__ flags; int /*<<< orphan*/  config_file; } ;
typedef  int /*<<< orphan*/  CK_UTF8CHAR_PTR ;
typedef  scalar_t__ CK_USER_TYPE ;
typedef  scalar_t__ CK_ULONG ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  scalar_t__ CK_RV ;

/* Variables and functions */
 scalar_t__ CKR_OK ; 
 scalar_t__ CKR_PIN_INCORRECT ; 
 int /*<<< orphan*/  INIT_CONTEXT () ; 
 int /*<<< orphan*/  NULL_PTR ; 
 int /*<<< orphan*/  VERIFY_SESSION_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ read_conf_file (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 TYPE_2__ soft_token ; 
 int /*<<< orphan*/  st_logf (char*,...) ; 

CK_RV
C_Login(CK_SESSION_HANDLE hSession,
	CK_USER_TYPE userType,
	CK_UTF8CHAR_PTR pPin,
	CK_ULONG ulPinLen)
{
    char *pin = NULL;
    CK_RV ret;
    INIT_CONTEXT();

    st_logf("Login\n");

    VERIFY_SESSION_HANDLE(hSession, NULL);

    if (pPin != NULL_PTR) {
	asprintf(&pin, "%.*s", (int)ulPinLen, pPin);
	st_logf("type: %d password: %s\n", (int)userType, pin);
    }

    /*
     * Login
     */

    ret = read_conf_file(soft_token.config_file, userType, pin);
    if (ret == CKR_OK)
	soft_token.flags.login_done = 1;

    free(pin);

    return soft_token.flags.login_done ? CKR_OK : CKR_PIN_INCORRECT;
}