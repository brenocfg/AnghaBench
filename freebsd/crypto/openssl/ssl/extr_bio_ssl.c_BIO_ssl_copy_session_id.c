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
struct TYPE_3__ {int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_1__ BIO_SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_TYPE_SSL ; 
 int /*<<< orphan*/ * BIO_find_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_copy_session_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int BIO_ssl_copy_session_id(BIO *t, BIO *f)
{
    BIO_SSL *tdata, *fdata;
    t = BIO_find_type(t, BIO_TYPE_SSL);
    f = BIO_find_type(f, BIO_TYPE_SSL);
    if ((t == NULL) || (f == NULL))
        return 0;
    tdata = BIO_get_data(t);
    fdata = BIO_get_data(f);
    if ((tdata->ssl == NULL) || (fdata->ssl == NULL))
        return 0;
    if (!SSL_copy_session_id(tdata->ssl, (fdata->ssl)))
        return 0;
    return 1;
}