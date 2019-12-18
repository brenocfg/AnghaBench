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
typedef  int /*<<< orphan*/  PKCS7 ;

/* Variables and functions */
 int /*<<< orphan*/  PKCS7_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS7_new () ; 
 int /*<<< orphan*/  PKCS7_set_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_set_type (int /*<<< orphan*/ *,int) ; 

int PKCS7_content_new(PKCS7 *p7, int type)
{
    PKCS7 *ret = NULL;

    if ((ret = PKCS7_new()) == NULL)
        goto err;
    if (!PKCS7_set_type(ret, type))
        goto err;
    if (!PKCS7_set_content(p7, ret))
        goto err;

    return 1;
 err:
    PKCS7_free(ret);
    return 0;
}