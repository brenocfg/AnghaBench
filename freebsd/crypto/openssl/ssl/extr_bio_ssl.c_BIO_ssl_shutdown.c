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
 scalar_t__ BIO_TYPE_SSL ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_method_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 

void BIO_ssl_shutdown(BIO *b)
{
    BIO_SSL *bdata;

    for (; b != NULL; b = BIO_next(b)) {
        if (BIO_method_type(b) != BIO_TYPE_SSL)
            continue;
        bdata = BIO_get_data(b);
        if (bdata != NULL && bdata->ssl != NULL)
            SSL_shutdown(bdata->ssl);
    }
}