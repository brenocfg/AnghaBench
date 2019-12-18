#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int sequence; } ;
typedef  TYPE_3__ X509_REVOKED ;
struct TYPE_8__ {int modified; } ;
struct TYPE_7__ {TYPE_2__ enc; int /*<<< orphan*/  revoked; } ;
struct TYPE_10__ {TYPE_1__ crl; } ;
typedef  TYPE_4__ X509_CRL ;

/* Variables and functions */
 int sk_X509_REVOKED_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_REVOKED_sort (int /*<<< orphan*/ ) ; 
 TYPE_3__* sk_X509_REVOKED_value (int /*<<< orphan*/ ,int) ; 

int X509_CRL_sort(X509_CRL *c)
{
    int i;
    X509_REVOKED *r;
    /*
     * sort the data so it will be written in serial number order
     */
    sk_X509_REVOKED_sort(c->crl.revoked);
    for (i = 0; i < sk_X509_REVOKED_num(c->crl.revoked); i++) {
        r = sk_X509_REVOKED_value(c->crl.revoked, i);
        r->sequence = i;
    }
    c->crl.enc.modified = 1;
    return 1;
}