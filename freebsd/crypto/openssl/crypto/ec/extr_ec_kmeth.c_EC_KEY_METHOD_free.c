#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ EC_KEY_METHOD ;

/* Variables and functions */
 int EC_KEY_METHOD_DYNAMIC ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

void EC_KEY_METHOD_free(EC_KEY_METHOD *meth)
{
    if (meth->flags & EC_KEY_METHOD_DYNAMIC)
        OPENSSL_free(meth);
}