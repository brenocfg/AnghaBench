#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  hx509_free_error_string (char*) ; 
 char* hx509_get_error_string (int /*<<< orphan*/ ,int) ; 
 int hx509_ocsp_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
verify_o(hx509_context hxcontext, void *ctx, hx509_cert c)
{
    heim_octet_string *os = ctx;
    time_t expiration;
    int ret;

    ret = hx509_ocsp_verify(context, 0, c, 0,
			    os->data, os->length, &expiration);
    if (ret) {
	char *s = hx509_get_error_string(hxcontext, ret);
	printf("ocsp_verify: %s: %d\n", s, ret);
	hx509_free_error_string(s);
    } else
	printf("expire: %d\n", (int)expiration);

    return ret;
}