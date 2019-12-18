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
struct TYPE_4__ {int flags; int /*<<< orphan*/  max; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ BUF_MEM ;

/* Variables and functions */
 int BUF_MEM_FLAG_SECURE ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_secure_clear_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void BUF_MEM_free(BUF_MEM *a)
{
    if (a == NULL)
        return;
    if (a->data != NULL) {
        if (a->flags & BUF_MEM_FLAG_SECURE)
            OPENSSL_secure_clear_free(a->data, a->max);
        else
            OPENSSL_clear_free(a->data, a->max);
    }
    OPENSSL_free(a);
}