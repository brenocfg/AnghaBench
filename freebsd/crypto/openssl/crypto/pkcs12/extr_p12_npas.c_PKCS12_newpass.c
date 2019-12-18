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
typedef  int /*<<< orphan*/  PKCS12 ;

/* Variables and functions */
 int /*<<< orphan*/  PKCS12_F_PKCS12_NEWPASS ; 
 int /*<<< orphan*/  PKCS12_R_INVALID_NULL_PKCS12_POINTER ; 
 int /*<<< orphan*/  PKCS12_R_MAC_VERIFY_FAILURE ; 
 int /*<<< orphan*/  PKCS12_R_PARSE_ERROR ; 
 int /*<<< orphan*/  PKCS12_verify_mac (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newpass_p12 (int /*<<< orphan*/ *,char const*,char const*) ; 

int PKCS12_newpass(PKCS12 *p12, const char *oldpass, const char *newpass)
{
    /* Check for NULL PKCS12 structure */

    if (!p12) {
        PKCS12err(PKCS12_F_PKCS12_NEWPASS,
                  PKCS12_R_INVALID_NULL_PKCS12_POINTER);
        return 0;
    }

    /* Check the mac */

    if (!PKCS12_verify_mac(p12, oldpass, -1)) {
        PKCS12err(PKCS12_F_PKCS12_NEWPASS, PKCS12_R_MAC_VERIFY_FAILURE);
        return 0;
    }

    if (!newpass_p12(p12, oldpass, newpass)) {
        PKCS12err(PKCS12_F_PKCS12_NEWPASS, PKCS12_R_PARSE_ERROR);
        return 0;
    }

    return 1;
}