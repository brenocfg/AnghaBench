#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_request ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_3__ {scalar_t__ name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hx509_name_to_string (scalar_t__,char**) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
_hx509_request_print(hx509_context context, hx509_request req, FILE *f)
{
    int ret;

    if (req->name) {
	char *subject;
	ret = hx509_name_to_string(req->name, &subject);
	if (ret) {
	    hx509_set_error_string(context, 0, ret, "Failed to print name");
	    return ret;
	}
        fprintf(f, "name: %s\n", subject);
	free(subject);
    }

    return 0;
}