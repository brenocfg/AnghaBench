#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ method_data; } ;
typedef  TYPE_1__ X509_LOOKUP ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer; int /*<<< orphan*/  dirs; } ;
typedef  TYPE_2__ BY_DIR ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  by_dir_entry_free ; 
 int /*<<< orphan*/  sk_BY_DIR_ENTRY_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_dir(X509_LOOKUP *lu)
{
    BY_DIR *a = (BY_DIR *)lu->method_data;

    sk_BY_DIR_ENTRY_pop_free(a->dirs, by_dir_entry_free);
    BUF_MEM_free(a->buffer);
    CRYPTO_THREAD_lock_free(a->lock);
    OPENSSL_free(a);
}