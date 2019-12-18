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
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  X509_VERIFY_PARAM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  param_cmp ; 
 int /*<<< orphan*/ * param_table ; 
 int /*<<< orphan*/ * sk_X509_VERIFY_PARAM_delete (int /*<<< orphan*/ *,int) ; 
 int sk_X509_VERIFY_PARAM_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_X509_VERIFY_PARAM_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_VERIFY_PARAM_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int X509_VERIFY_PARAM_add0_table(X509_VERIFY_PARAM *param)
{
    int idx;
    X509_VERIFY_PARAM *ptmp;
    if (param_table == NULL) {
        param_table = sk_X509_VERIFY_PARAM_new(param_cmp);
        if (param_table == NULL)
            return 0;
    } else {
        idx = sk_X509_VERIFY_PARAM_find(param_table, param);
        if (idx >= 0) {
            ptmp = sk_X509_VERIFY_PARAM_delete(param_table, idx);
            X509_VERIFY_PARAM_free(ptmp);
        }
    }
    if (!sk_X509_VERIFY_PARAM_push(param_table, param))
        return 0;
    return 1;
}