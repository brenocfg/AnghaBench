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
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ RSA_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char const*) ; 
 int /*<<< orphan*/  RSA_F_RSA_METH_SET1_NAME ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int RSA_meth_set1_name(RSA_METHOD *meth, const char *name)
{
    char *tmpname = OPENSSL_strdup(name);

    if (tmpname == NULL) {
        RSAerr(RSA_F_RSA_METH_SET1_NAME, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    OPENSSL_free(meth->name);
    meth->name = tmpname;

    return 1;
}