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
 int /*<<< orphan*/  BIO_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_rbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_get_wbio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set0_rbio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set0_wbio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SSL_set_bio(SSL *s, BIO *rbio, BIO *wbio)
{
    /*
     * For historical reasons, this function has many different cases in
     * ownership handling.
     */

    /* If nothing has changed, do nothing */
    if (rbio == SSL_get_rbio(s) && wbio == SSL_get_wbio(s))
        return;

    /*
     * If the two arguments are equal then one fewer reference is granted by the
     * caller than we want to take
     */
    if (rbio != NULL && rbio == wbio)
        BIO_up_ref(rbio);

    /*
     * If only the wbio is changed only adopt one reference.
     */
    if (rbio == SSL_get_rbio(s)) {
        SSL_set0_wbio(s, wbio);
        return;
    }
    /*
     * There is an asymmetry here for historical reasons. If only the rbio is
     * changed AND the rbio and wbio were originally different, then we only
     * adopt one reference.
     */
    if (wbio == SSL_get_wbio(s) && SSL_get_rbio(s) != SSL_get_wbio(s)) {
        SSL_set0_rbio(s, rbio);
        return;
    }

    /* Otherwise, adopt both references. */
    SSL_set0_rbio(s, rbio);
    SSL_set0_wbio(s, wbio);
}