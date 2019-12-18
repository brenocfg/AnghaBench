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
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_certs ;

/* Variables and functions */
 int /*<<< orphan*/  hx509_certs_free (int /*<<< orphan*/ *) ; 
 int hx509_certs_init (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_certs_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
hx509_certs_append(hx509_context context,
		   hx509_certs to,
		   hx509_lock lock,
		   const char *name)
{
    hx509_certs s;
    int ret;

    ret = hx509_certs_init(context, name, 0, lock, &s);
    if (ret)
	return ret;
    ret = hx509_certs_merge(context, to, s);
    hx509_certs_free(&s);
    return ret;
}