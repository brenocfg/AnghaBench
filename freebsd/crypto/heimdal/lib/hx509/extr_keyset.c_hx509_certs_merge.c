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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/ * hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  certs_merge_func ; 
 int hx509_certs_iter_f (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
hx509_certs_merge(hx509_context context, hx509_certs to, hx509_certs from)
{
    if (from == NULL)
	return 0;
    return hx509_certs_iter_f(context, from, certs_merge_func, to);
}