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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 char* EC_curve_nid2nist (int) ; 
 char* OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OPENSSL_free (int*) ; 
 int SSL_get1_groups (int /*<<< orphan*/ *,int*) ; 
 int SSL_get_shared_group (int /*<<< orphan*/ *,int) ; 
 int TLSEXT_nid_unknown ; 
 int* app_malloc (int,char*) ; 

int ssl_print_groups(BIO *out, SSL *s, int noshared)
{
    int i, ngroups, *groups, nid;
    const char *gname;

    ngroups = SSL_get1_groups(s, NULL);
    if (ngroups <= 0)
        return 1;
    groups = app_malloc(ngroups * sizeof(int), "groups to print");
    SSL_get1_groups(s, groups);

    BIO_puts(out, "Supported Elliptic Groups: ");
    for (i = 0; i < ngroups; i++) {
        if (i)
            BIO_puts(out, ":");
        nid = groups[i];
        /* If unrecognised print out hex version */
        if (nid & TLSEXT_nid_unknown) {
            BIO_printf(out, "0x%04X", nid & 0xFFFF);
        } else {
            /* TODO(TLS1.3): Get group name here */
            /* Use NIST name for curve if it exists */
            gname = EC_curve_nid2nist(nid);
            if (gname == NULL)
                gname = OBJ_nid2sn(nid);
            BIO_printf(out, "%s", gname);
        }
    }
    OPENSSL_free(groups);
    if (noshared) {
        BIO_puts(out, "\n");
        return 1;
    }
    BIO_puts(out, "\nShared Elliptic groups: ");
    ngroups = SSL_get_shared_group(s, -1);
    for (i = 0; i < ngroups; i++) {
        if (i)
            BIO_puts(out, ":");
        nid = SSL_get_shared_group(s, i);
        /* TODO(TLS1.3): Convert for DH groups */
        gname = EC_curve_nid2nist(nid);
        if (gname == NULL)
            gname = OBJ_nid2sn(nid);
        BIO_printf(out, "%s", gname);
    }
    if (ngroups == 0)
        BIO_puts(out, "NONE");
    BIO_puts(out, "\n");
    return 1;
}