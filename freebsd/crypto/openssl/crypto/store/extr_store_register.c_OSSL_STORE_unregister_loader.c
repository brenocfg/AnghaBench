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
typedef  int /*<<< orphan*/  OSSL_STORE_LOADER ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_store_init_once () ; 
 int /*<<< orphan*/ * ossl_store_unregister_loader_int (char const*) ; 

OSSL_STORE_LOADER *OSSL_STORE_unregister_loader(const char *scheme)
{
    if (!ossl_store_init_once())
        return 0;
    return ossl_store_unregister_loader_int(scheme);
}