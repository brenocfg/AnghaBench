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
struct TYPE_3__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ hx509_path ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  hx509_cert_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

int
_hx509_path_append(hx509_context context, hx509_path *path, hx509_cert cert)
{
    hx509_cert *val;
    val = realloc(path->val, (path->len + 1) * sizeof(path->val[0]));
    if (val == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    path->val = val;
    path->val[path->len] = hx509_cert_ref(cert);
    path->len++;

    return 0;
}