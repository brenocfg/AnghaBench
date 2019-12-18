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
typedef  int /*<<< orphan*/  hx509_pem_header ;
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hx509_cert_get_subject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int hx509_name_to_string (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  hx509_pem_add_header (int /*<<< orphan*/ **,char*,char*) ; 

__attribute__((used)) static int
print_signer(hx509_context contextp, void *ctx, hx509_cert cert)
{
    hx509_pem_header **header = ctx;
    char *signer_name = NULL;
    hx509_name name;
    int ret;

    ret = hx509_cert_get_subject(cert, &name);
    if (ret)
	errx(1, "hx509_cert_get_subject");

    ret = hx509_name_to_string(name, &signer_name);
    hx509_name_free(&name);
    if (ret)
	errx(1, "hx509_name_to_string");

    hx509_pem_add_header(header, "Signer", signer_name);

    free(signer_name);
    return 0;
}