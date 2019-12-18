#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_4__ {int /*<<< orphan*/  issuer; int /*<<< orphan*/  subject; } ;
struct TYPE_5__ {TYPE_1__ tbsCertificate; } ;
typedef  TYPE_2__ Certificate ;

/* Variables and functions */
 TYPE_2__* _hx509_get_cert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hx509_name_from_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (void*,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_name_to_string (int /*<<< orphan*/ ,char**) ; 

int
hx509_ci_print_names(hx509_context context, void *ctx, hx509_cert c)
{
    Certificate *cert;
    hx509_name n;
    char *s, *i;

    cert = _hx509_get_cert(c);

    _hx509_name_from_Name(&cert->tbsCertificate.subject, &n);
    hx509_name_to_string(n, &s);
    hx509_name_free(&n);
    _hx509_name_from_Name(&cert->tbsCertificate.issuer, &n);
    hx509_name_to_string(n, &i);
    hx509_name_free(&n);
    fprintf(ctx, "subject: %s\nissuer: %s\n", s, i);
    free(s);
    free(i);
    return 0;
}