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
struct TYPE_4__ {char const* file; int line; char const* info; int references; struct TYPE_4__* next; int /*<<< orphan*/  threadid; } ;
typedef  TYPE_1__ APP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_DISABLE ; 
 int /*<<< orphan*/  CRYPTO_MEM_CHECK_ENABLE ; 
 int /*<<< orphan*/  CRYPTO_THREAD_get_current_id () ; 
 scalar_t__ CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CRYPTO_mem_ctrl (int /*<<< orphan*/ ) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appinfokey ; 
 int /*<<< orphan*/  do_memdbg_init ; 
 scalar_t__ mem_check_on () ; 
 int /*<<< orphan*/  memdbg_init ; 

int CRYPTO_mem_debug_push(const char *info, const char *file, int line)
{
    APP_INFO *ami, *amim;
    int ret = 0;

    if (mem_check_on()) {
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_DISABLE);

        if (!RUN_ONCE(&memdbg_init, do_memdbg_init)
            || (ami = OPENSSL_malloc(sizeof(*ami))) == NULL)
            goto err;

        ami->threadid = CRYPTO_THREAD_get_current_id();
        ami->file = file;
        ami->line = line;
        ami->info = info;
        ami->references = 1;
        ami->next = NULL;

        amim = (APP_INFO *)CRYPTO_THREAD_get_local(&appinfokey);
        CRYPTO_THREAD_set_local(&appinfokey, ami);

        if (amim != NULL)
            ami->next = amim;
        ret = 1;
 err:
        CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ENABLE);
    }

    return ret;
}