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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_accept () ; 
 scalar_t__ BIO_set_accept_name (int /*<<< orphan*/ *,char const*) ; 

BIO *BIO_new_accept(const char *str)
{
    BIO *ret;

    ret = BIO_new(BIO_s_accept());
    if (ret == NULL)
        return NULL;
    if (BIO_set_accept_name(ret, str))
        return ret;
    BIO_free(ret);
    return NULL;
}