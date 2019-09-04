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
struct TYPE_3__ {int /*<<< orphan*/  base; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  i2d_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * openPemFile (char*) ; 
 int /*<<< orphan*/  stderr ; 

int get_certificates(char * pem_fname, ptls_iovec_t ** list, int * nb_certs)
{
    int ret = 0;
    size_t count = 0;
    X509 *cert;
    static ptls_iovec_t certs[16];

    *nb_certs = 0;
    *list = NULL;

    cert = openPemFile(pem_fname);

    if (cert == NULL)
    {
        fprintf(stderr, "Could not read cert in %s\n", pem_fname);
        ret = -1;
    }
    else
    {
        ptls_iovec_t *dst = certs + count++;
        dst->len = i2d_X509(cert, &dst->base);
    }
    
    *nb_certs = (int) count;
    *list = certs;

    return ret;
}