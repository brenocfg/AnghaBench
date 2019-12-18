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
struct certificate_copy_options {int /*<<< orphan*/  out_pass_string; int /*<<< orphan*/  in_pass_strings; } ;
typedef  int /*<<< orphan*/ * hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_CERTS_CREATE ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int) ; 
 int hx509_certs_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_certs_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int hx509_lock_command_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
certificate_copy(struct certificate_copy_options *opt, int argc, char **argv)
{
    hx509_certs certs;
    hx509_lock inlock, outlock = NULL;
    int ret;

    hx509_lock_init(context, &inlock);
    lock_strings(inlock, &opt->in_pass_strings);

    if (opt->out_pass_string) {
	hx509_lock_init(context, &outlock);
	ret = hx509_lock_command_string(outlock, opt->out_pass_string);
	if (ret)
	    errx(1, "hx509_lock_command_string: %s: %d",
		 opt->out_pass_string, ret);
    }

    ret = hx509_certs_init(context, argv[argc - 1],
			   HX509_CERTS_CREATE, inlock, &certs);
    if (ret)
	hx509_err(context, 1, ret, "hx509_certs_init");

    while(argc-- > 1) {
	int retx;
	retx = hx509_certs_append(context, certs, inlock, argv[0]);
	if (retx)
	    hx509_err(context, 1, retx, "hx509_certs_append");
	argv++;
    }

    ret = hx509_certs_store(context, certs, 0, outlock);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_certs_store");

    hx509_certs_free(&certs);
    hx509_lock_free(inlock);
    hx509_lock_free(outlock);

    return 0;
}