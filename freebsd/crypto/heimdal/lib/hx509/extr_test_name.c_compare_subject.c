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
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int hx509_cert_get_subject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hx509_name_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hx509_name_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
compare_subject(hx509_cert c1, hx509_cert c2, int *l)
{
    hx509_name n1, n2;
    int ret;

    ret = hx509_cert_get_subject(c1, &n1);
    if (ret) return 1;
    ret = hx509_cert_get_subject(c2, &n2);
    if (ret) return 1;

    *l = hx509_name_cmp(n1, n2);
    hx509_name_free(&n1);
    hx509_name_free(&n2);

    return 0;
}