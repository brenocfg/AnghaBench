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
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ i2a_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int save_ts_serial(const char *serialfile, ASN1_INTEGER *serial)
{
    int ret = 0;
    BIO *out = NULL;

    if ((out = BIO_new_file(serialfile, "w")) == NULL)
        goto err;
    if (i2a_ASN1_INTEGER(out, serial) <= 0)
        goto err;
    if (BIO_puts(out, "\n") <= 0)
        goto err;
    ret = 1;
 err:
    if (!ret)
        BIO_printf(bio_err, "could not save serial number to %s\n",
                   serialfile);
    BIO_free_all(out);
    return ret;
}