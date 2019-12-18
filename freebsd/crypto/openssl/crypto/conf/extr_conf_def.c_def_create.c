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
struct TYPE_3__ {scalar_t__ (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ CONF_METHOD ;
typedef  int /*<<< orphan*/  CONF ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static CONF *def_create(CONF_METHOD *meth)
{
    CONF *ret;

    ret = OPENSSL_malloc(sizeof(*ret));
    if (ret != NULL)
        if (meth->init(ret) == 0) {
            OPENSSL_free(ret);
            ret = NULL;
        }
    return ret;
}