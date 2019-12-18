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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int X509V3_EXT_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int X509V3_EXT_print_fp(FILE *fp, X509_EXTENSION *ext, int flag, int indent)
{
    BIO *bio_tmp;
    int ret;

    if ((bio_tmp = BIO_new_fp(fp, BIO_NOCLOSE)) == NULL)
        return 0;
    ret = X509V3_EXT_print(bio_tmp, ext, flag, indent);
    BIO_free(bio_tmp);
    return ret;
}