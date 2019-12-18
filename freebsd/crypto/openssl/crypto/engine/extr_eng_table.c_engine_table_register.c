#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int nid; int uptodate; int /*<<< orphan*/ * funct; int /*<<< orphan*/  sk; } ;
struct TYPE_10__ {int /*<<< orphan*/  piles; } ;
typedef  TYPE_1__ ENGINE_TABLE ;
typedef  TYPE_2__ ENGINE_PILE ;
typedef  int /*<<< orphan*/  ENGINE_CLEANUP_CB ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_TABLE_REGISTER ; 
 int /*<<< orphan*/  ENGINE_R_INIT_FAILED ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  engine_cleanup_add_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  engine_unlocked_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  engine_unlocked_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_engine_lock ; 
 int /*<<< orphan*/  int_table_check (TYPE_1__**,int) ; 
 int /*<<< orphan*/  lh_ENGINE_PILE_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* lh_ENGINE_PILE_retrieve (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  sk_ENGINE_delete_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_ENGINE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_ENGINE_new_null () ; 
 int /*<<< orphan*/  sk_ENGINE_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int engine_table_register(ENGINE_TABLE **table, ENGINE_CLEANUP_CB *cleanup,
                          ENGINE *e, const int *nids, int num_nids,
                          int setdefault)
{
    int ret = 0, added = 0;
    ENGINE_PILE tmplate, *fnd;
    CRYPTO_THREAD_write_lock(global_engine_lock);
    if (!(*table))
        added = 1;
    if (!int_table_check(table, 1))
        goto end;
    if (added)
        /* The cleanup callback needs to be added */
        engine_cleanup_add_first(cleanup);
    while (num_nids--) {
        tmplate.nid = *nids;
        fnd = lh_ENGINE_PILE_retrieve(&(*table)->piles, &tmplate);
        if (!fnd) {
            fnd = OPENSSL_malloc(sizeof(*fnd));
            if (fnd == NULL)
                goto end;
            fnd->uptodate = 1;
            fnd->nid = *nids;
            fnd->sk = sk_ENGINE_new_null();
            if (!fnd->sk) {
                OPENSSL_free(fnd);
                goto end;
            }
            fnd->funct = NULL;
            (void)lh_ENGINE_PILE_insert(&(*table)->piles, fnd);
            if (lh_ENGINE_PILE_retrieve(&(*table)->piles, &tmplate) != fnd) {
                sk_ENGINE_free(fnd->sk);
                OPENSSL_free(fnd);
                goto end;
            }
        }
        /* A registration shouldn't add duplicate entries */
        (void)sk_ENGINE_delete_ptr(fnd->sk, e);
        /*
         * if 'setdefault', this ENGINE goes to the head of the list
         */
        if (!sk_ENGINE_push(fnd->sk, e))
            goto end;
        /* "touch" this ENGINE_PILE */
        fnd->uptodate = 0;
        if (setdefault) {
            if (!engine_unlocked_init(e)) {
                ENGINEerr(ENGINE_F_ENGINE_TABLE_REGISTER,
                          ENGINE_R_INIT_FAILED);
                goto end;
            }
            if (fnd->funct)
                engine_unlocked_finish(fnd->funct, 0);
            fnd->funct = e;
            fnd->uptodate = 1;
        }
        nids++;
    }
    ret = 1;
 end:
    CRYPTO_THREAD_unlock(global_engine_lock);
    return ret;
}