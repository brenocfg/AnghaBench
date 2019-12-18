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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int ENOMEM ; 
 int _hx509_name_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  asn1_oid_id_at_commonName ; 
 int /*<<< orphan*/  asprintf (char**,char*,unsigned long) ; 
 int copy_Name (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_Name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
build_proxy_prefix(hx509_context context, const Name *issuer, Name *subject)
{
    char *tstr;
    time_t t;
    int ret;

    ret = copy_Name(issuer, subject);
    if (ret) {
	hx509_set_error_string(context, 0, ret,
			       "Failed to copy subject name");
	return ret;
    }

    t = time(NULL);
    asprintf(&tstr, "ts-%lu", (unsigned long)t);
    if (tstr == NULL) {
	hx509_set_error_string(context, 0, ENOMEM,
			       "Failed to copy subject name");
	return ENOMEM;
    }
    /* prefix with CN=<ts>,...*/
    ret = _hx509_name_modify(context, subject, 1, &asn1_oid_id_at_commonName, tstr);
    free(tstr);
    if (ret)
	free_Name(subject);
    return ret;
}