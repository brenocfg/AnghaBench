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
struct foo {char* id; char* label; } ;
typedef  int /*<<< orphan*/ * hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/  CK_RV ;

/* Variables and functions */
 int /*<<< orphan*/  CKR_GENERAL_ERROR ; 
 int /*<<< orphan*/  CKR_OK ; 
 int HX509_CERTS_UNPROTECT_ALL ; 
 int /*<<< orphan*/  add_cert ; 
 int /*<<< orphan*/  asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct foo*) ; 
 int /*<<< orphan*/  hx509_lock_command_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_logf (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static CK_RV
add_certificate(const char *cert_file,
		const char *pin,
		char *id,
		char *label)
{
    hx509_certs certs;
    hx509_lock lock = NULL;
    int ret, flags = 0;

    struct foo foo;
    foo.id = id;
    foo.label = label;

    if (pin == NULL)
	flags |= HX509_CERTS_UNPROTECT_ALL;

    if (pin) {
	char *str;
	asprintf(&str, "PASS:%s", pin);

	hx509_lock_init(context, &lock);
	hx509_lock_command_string(lock, str);

	memset(str, 0, strlen(str));
	free(str);
    }

    ret = hx509_certs_init(context, cert_file, flags, lock, &certs);
    if (ret) {
	st_logf("failed to open file %s\n", cert_file);
	return CKR_GENERAL_ERROR;
    }

    ret = hx509_certs_iter_f(context, certs, add_cert, &foo);
    hx509_certs_free(&certs);
    if (ret) {
	st_logf("failed adding certs from file %s\n", cert_file);
	return CKR_GENERAL_ERROR;
    }

    return CKR_OK;
}