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

/* Variables and functions */
 int /*<<< orphan*/  DTLS1_BAD_VER ; 
#define  DTLS_ANY_VERSION 129 
 int /*<<< orphan*/  DTLS_MAX_VERSION ; 
 int /*<<< orphan*/  DTLS_VERSION_GT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTLS_VERSION_LT (int,int /*<<< orphan*/ ) ; 
 int SSL3_VERSION ; 
#define  TLS_ANY_VERSION 128 
 int TLS_MAX_VERSION ; 

int ssl_set_version_bound(int method_version, int version, int *bound)
{
    if (version == 0) {
        *bound = version;
        return 1;
    }

    /*-
     * Restrict TLS methods to TLS protocol versions.
     * Restrict DTLS methods to DTLS protocol versions.
     * Note, DTLS version numbers are decreasing, use comparison macros.
     *
     * Note that for both lower-bounds we use explicit versions, not
     * (D)TLS_MIN_VERSION.  This is because we don't want to break user
     * configurations.  If the MIN (supported) version ever rises, the user's
     * "floor" remains valid even if no longer available.  We don't expect the
     * MAX ceiling to ever get lower, so making that variable makes sense.
     */
    switch (method_version) {
    default:
        /*
         * XXX For fixed version methods, should we always fail and not set any
         * bounds, always succeed and not set any bounds, or set the bounds and
         * arrange to fail later if they are not met?  At present fixed-version
         * methods are not subject to controls that disable individual protocol
         * versions.
         */
        return 0;

    case TLS_ANY_VERSION:
        if (version < SSL3_VERSION || version > TLS_MAX_VERSION)
            return 0;
        break;

    case DTLS_ANY_VERSION:
        if (DTLS_VERSION_GT(version, DTLS_MAX_VERSION) ||
            DTLS_VERSION_LT(version, DTLS1_BAD_VER))
            return 0;
        break;
    }

    *bound = version;
    return 1;
}