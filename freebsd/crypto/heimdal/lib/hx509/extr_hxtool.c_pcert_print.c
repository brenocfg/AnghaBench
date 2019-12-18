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
struct print_s {int /*<<< orphan*/  verbose; scalar_t__ counter; } ;
struct print_options {scalar_t__ info_flag; scalar_t__ never_fail_flag; int /*<<< orphan*/  pass_strings; int /*<<< orphan*/  content_flag; } ;
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct print_s*) ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  hx509_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_lock_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_f ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
pcert_print(struct print_options *opt, int argc, char **argv)
{
    hx509_certs certs;
    hx509_lock lock;
    struct print_s s;

    s.counter = 0;
    s.verbose = opt->content_flag;

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    while(argc--) {
	int ret;
	ret = hx509_certs_init(context, argv[0], 0, lock, &certs);
	if (ret) {
	    if (opt->never_fail_flag) {
		printf("ignoreing failure: %d\n", ret);
		continue;
	    }
	    hx509_err(context, 1, ret, "hx509_certs_init");
	}
	if (opt->info_flag)
	    hx509_certs_info(context, certs, NULL, NULL);
	hx509_certs_iter_f(context, certs, print_f, &s);
	hx509_certs_free(&certs);
	argv++;
    }

    hx509_lock_free(lock);

    return 0;
}