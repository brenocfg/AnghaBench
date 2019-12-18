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
struct TYPE_3__ {int /*<<< orphan*/ * extensions; } ;
typedef  TYPE_1__ TS_TST_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  X509_EXTENSION_free ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void TS_TST_INFO_ext_free(TS_TST_INFO *a)
{
    if (!a)
        return;
    sk_X509_EXTENSION_pop_free(a->extensions, X509_EXTENSION_free);
    a->extensions = NULL;
}