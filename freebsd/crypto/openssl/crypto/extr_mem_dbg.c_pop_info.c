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
struct TYPE_4__ {scalar_t__ references; struct TYPE_4__* next; } ;
typedef  TYPE_1__ APP_INFO ;

/* Variables and functions */
 scalar_t__ CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appinfokey ; 
 int /*<<< orphan*/  do_memdbg_init ; 
 int /*<<< orphan*/  memdbg_init ; 

__attribute__((used)) static int pop_info(void)
{
    APP_INFO *current = NULL;

    if (!RUN_ONCE(&memdbg_init, do_memdbg_init))
        return 0;

    current = (APP_INFO *)CRYPTO_THREAD_get_local(&appinfokey);
    if (current != NULL) {
        APP_INFO *next = current->next;

        if (next != NULL) {
            next->references++;
            CRYPTO_THREAD_set_local(&appinfokey, next);
        } else {
            CRYPTO_THREAD_set_local(&appinfokey, NULL);
        }
        if (--(current->references) <= 0) {
            current->next = NULL;
            if (next != NULL)
                next->references--;
            OPENSSL_free(current);
        }
        return 1;
    }
    return 0;
}