#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_crl ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_5__ {scalar_t__ expire; int /*<<< orphan*/  revoked; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int
hx509_crl_alloc(hx509_context context, hx509_crl *crl)
{
    int ret;

    *crl = calloc(1, sizeof(**crl));
    if (*crl == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    ret = hx509_certs_init(context, "MEMORY:crl", 0, NULL, &(*crl)->revoked);
    if (ret) {
	free(*crl);
	*crl = NULL;
	return ret;
    }
    (*crl)->expire = 0;
    return ret;
}