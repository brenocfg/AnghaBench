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
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
typedef  int /*<<< orphan*/  heim_integer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_heim_integer (int /*<<< orphan*/ *) ; 
 int der_print_hex_heim_integer (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hx509_cert_get_issuer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_cert_get_serialnumber (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_cert_get_subject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_cert_keyusage_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_name_to_string (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * stderr ; 

int
hx509_print_cert(hx509_context context, hx509_cert cert, FILE *out)
{
    hx509_name name;
    char *str;
    int ret;

    if (out == NULL)
	out = stderr;

    ret = hx509_cert_get_issuer(cert, &name);
    if (ret)
	return ret;
    hx509_name_to_string(name, &str);
    hx509_name_free(&name);
    fprintf(out, "    issuer:  \"%s\"\n", str);
    free(str);

    ret = hx509_cert_get_subject(cert, &name);
    if (ret)
	return ret;
    hx509_name_to_string(name, &str);
    hx509_name_free(&name);
    fprintf(out, "    subject: \"%s\"\n", str);
    free(str);

    {
	heim_integer serialNumber;

	ret = hx509_cert_get_serialnumber(cert, &serialNumber);
	if (ret)
	    return ret;
	ret = der_print_hex_heim_integer(&serialNumber, &str);
	if (ret)
	    return ret;
	der_free_heim_integer(&serialNumber);
	fprintf(out, "    serial: %s\n", str);
	free(str);
    }

    printf("    keyusage: ");
    ret = hx509_cert_keyusage_print(context, cert, &str);
    if (ret == 0) {
	fprintf(out, "%s\n", str);
	free(str);
    } else
	fprintf(out, "no");

    return 0;
}