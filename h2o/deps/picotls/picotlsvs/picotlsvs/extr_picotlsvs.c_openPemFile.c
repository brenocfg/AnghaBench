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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_new () ; 

X509* openPemFile(char* filename)
{

    X509* cert = X509_new();
    BIO* bio_cert = BIO_new_file(filename, "rb");
    PEM_read_bio_X509(bio_cert, &cert, NULL, NULL);
    return cert;
}