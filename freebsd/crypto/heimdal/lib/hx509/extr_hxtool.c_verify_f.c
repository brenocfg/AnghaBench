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
struct verify {int /*<<< orphan*/  errors; scalar_t__ hostname; int /*<<< orphan*/  count; int /*<<< orphan*/  chain; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_HN_HOSTNAME ; 
 int /*<<< orphan*/  hx509_free_error_string (char*) ; 
 char* hx509_get_error_string (int /*<<< orphan*/ ,int) ; 
 int hx509_verify_hostname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hx509_verify_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
verify_f(hx509_context hxcontext, void *ctx, hx509_cert c)
{
    struct verify *v = ctx;
    int ret;

    ret = hx509_verify_path(hxcontext, v->ctx, c, v->chain);
    if (ret) {
	char *s = hx509_get_error_string(hxcontext, ret);
	printf("verify_path: %s: %d\n", s, ret);
	hx509_free_error_string(s);
	v->errors++;
    } else {
	v->count++;
	printf("path ok\n");
    }

    if (v->hostname) {
	ret = hx509_verify_hostname(hxcontext, c, 0, HX509_HN_HOSTNAME,
				    v->hostname, NULL, 0);
	if (ret) {
	    printf("verify_hostname: %d\n", ret);
	    v->errors++;
	}
    }

    return 0;
}