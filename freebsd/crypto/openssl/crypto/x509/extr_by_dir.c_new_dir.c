#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* method_data; } ;
typedef  TYPE_1__ X509_LOOKUP ;
struct TYPE_7__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * dirs; } ;
typedef  TYPE_2__ BY_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BUF_MEM_new () ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  X509_F_NEW_DIR ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int new_dir(X509_LOOKUP *lu)
{
    BY_DIR *a = OPENSSL_malloc(sizeof(*a));

    if (a == NULL) {
        X509err(X509_F_NEW_DIR, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    if ((a->buffer = BUF_MEM_new()) == NULL) {
        X509err(X509_F_NEW_DIR, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    a->dirs = NULL;
    a->lock = CRYPTO_THREAD_lock_new();
    if (a->lock == NULL) {
        BUF_MEM_free(a->buffer);
        X509err(X509_F_NEW_DIR, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    lu->method_data = a;
    return 1;

 err:
    OPENSSL_free(a);
    return 0;
}