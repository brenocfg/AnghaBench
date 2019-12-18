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
struct ocsp_verify_options {int /*<<< orphan*/ * ocsp_file_string; } ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;
typedef  int /*<<< orphan*/  heim_octet_string ;

/* Variables and functions */
 int _hx509_map_file_os (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hx509_unmap_file_os (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  err (int,char*,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int hx509_certs_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*,...) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_o ; 

int
ocsp_verify(struct ocsp_verify_options *opt, int argc, char **argv)
{
    hx509_lock lock;
    hx509_certs certs;
    int ret, i;
    heim_octet_string os;

    hx509_lock_init(context, &lock);

    if (opt->ocsp_file_string == NULL)
	errx(1, "no ocsp file given");

    ret = _hx509_map_file_os(opt->ocsp_file_string, &os);
    if (ret)
	err(1, "map_file: %s: %d", argv[0], ret);

    ret = hx509_certs_init(context, "MEMORY:test-certs", 0, NULL, &certs);
    if (ret) hx509_err(context, 1, ret, "hx509_certs_init: MEMORY");

    for (i = 0; i < argc; i++) {
	ret = hx509_certs_append(context, certs, lock, argv[i]);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_certs_append: %s", argv[i]);
    }

    ret = hx509_certs_iter_f(context, certs, verify_o, &os);

    hx509_certs_free(&certs);
    _hx509_unmap_file_os(&os);
    hx509_lock_free(lock);

    return ret;
}