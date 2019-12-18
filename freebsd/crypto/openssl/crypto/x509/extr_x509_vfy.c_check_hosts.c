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
struct TYPE_3__ {int /*<<< orphan*/ * peername; int /*<<< orphan*/  hostflags; int /*<<< orphan*/  hosts; } ;
typedef  TYPE_1__ X509_VERIFY_PARAM ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_check_host (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int sk_OPENSSL_STRING_num (int /*<<< orphan*/ ) ; 
 char* sk_OPENSSL_STRING_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_hosts(X509 *x, X509_VERIFY_PARAM *vpm)
{
    int i;
    int n = sk_OPENSSL_STRING_num(vpm->hosts);
    char *name;

    if (vpm->peername != NULL) {
        OPENSSL_free(vpm->peername);
        vpm->peername = NULL;
    }
    for (i = 0; i < n; ++i) {
        name = sk_OPENSSL_STRING_value(vpm->hosts, i);
        if (X509_check_host(x, name, 0, vpm->hostflags, &vpm->peername) > 0)
            return 1;
    }
    return n == 0;
}