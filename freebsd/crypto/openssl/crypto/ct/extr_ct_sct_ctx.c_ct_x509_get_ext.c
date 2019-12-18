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
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 scalar_t__ X509_get_ext_by_NID (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int ct_x509_get_ext(X509 *cert, int nid, int *is_duplicated)
{
    int ret = X509_get_ext_by_NID(cert, nid, -1);

    if (is_duplicated != NULL)
        *is_duplicated = ret >= 0 && X509_get_ext_by_NID(cert, nid, ret) >= 0;

    return ret;
}