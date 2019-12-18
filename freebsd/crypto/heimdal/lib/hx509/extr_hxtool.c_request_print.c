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
struct request_print_options {int dummy; } ;
typedef  int /*<<< orphan*/  hx509_request ;

/* Variables and functions */
 int _hx509_request_parse (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int _hx509_request_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  hx509_err (int /*<<< orphan*/ ,int,int,char*,char*) ; 
 int /*<<< orphan*/  hx509_request_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

int
request_print(struct request_print_options *opt, int argc, char **argv)
{
    int ret, i;

    printf("request print\n");

    for (i = 0; i < argc; i++) {
	hx509_request req;

	ret = _hx509_request_parse(context, argv[i], &req);
	if (ret)
	    hx509_err(context, 1, ret, "parse_request: %s", argv[i]);

	ret = _hx509_request_print(context, req, stdout);
	hx509_request_free(&req);
	if (ret)
	    hx509_err(context, 1, ret, "Failed to print file %s", argv[i]);
    }

    return 0;
}