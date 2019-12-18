#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ canon_enclen; int /*<<< orphan*/  canon_enc; scalar_t__ modified; } ;
typedef  TYPE_1__ X509_NAME ;

/* Variables and functions */
 int X509_V_ERR_OUT_OF_MEM ; 
 int X509_V_ERR_PERMITTED_VIOLATION ; 
 int X509_V_OK ; 
 scalar_t__ i2d_X509_NAME (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nc_dn(X509_NAME *nm, X509_NAME *base)
{
    /* Ensure canonical encodings are up to date.  */
    if (nm->modified && i2d_X509_NAME(nm, NULL) < 0)
        return X509_V_ERR_OUT_OF_MEM;
    if (base->modified && i2d_X509_NAME(base, NULL) < 0)
        return X509_V_ERR_OUT_OF_MEM;
    if (base->canon_enclen > nm->canon_enclen)
        return X509_V_ERR_PERMITTED_VIOLATION;
    if (memcmp(base->canon_enc, nm->canon_enc, base->canon_enclen))
        return X509_V_ERR_PERMITTED_VIOLATION;
    return X509_V_OK;
}