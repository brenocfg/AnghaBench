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
typedef  int /*<<< orphan*/  X509_PURPOSE ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 char* X509_PURPOSE_get0_name (int /*<<< orphan*/ *) ; 
 int X509_PURPOSE_get_id (int /*<<< orphan*/ *) ; 
 int X509_check_purpose (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int purpose_print(BIO *bio, X509 *cert, X509_PURPOSE *pt)
{
    int id, i, idret;
    const char *pname;
    id = X509_PURPOSE_get_id(pt);
    pname = X509_PURPOSE_get0_name(pt);
    for (i = 0; i < 2; i++) {
        idret = X509_check_purpose(cert, id, i);
        BIO_printf(bio, "%s%s : ", pname, i ? " CA" : "");
        if (idret == 1)
            BIO_printf(bio, "Yes\n");
        else if (idret == 0)
            BIO_printf(bio, "No\n");
        else
            BIO_printf(bio, "Yes (WARNING code=%d)\n", idret);
    }
    return 1;
}