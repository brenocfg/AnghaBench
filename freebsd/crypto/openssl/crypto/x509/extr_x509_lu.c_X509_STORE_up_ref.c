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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  references; } ;
typedef  TYPE_1__ X509_STORE ;

/* Variables and functions */
 scalar_t__ CRYPTO_UP_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a ; 

int X509_STORE_up_ref(X509_STORE *vfy)
{
    int i;

    if (CRYPTO_UP_REF(&vfy->references, &i, vfy->lock) <= 0)
        return 0;

    REF_PRINT_COUNT("X509_STORE", a);
    REF_ASSERT_ISNT(i < 2);
    return ((i > 1) ? 1 : 0);
}