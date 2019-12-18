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
struct TYPE_11__ {int shutdown; int references; int init; int /*<<< orphan*/ * lock; int /*<<< orphan*/  ex_data; TYPE_1__ const* method; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* create ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ BIO_METHOD ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_BIO_NEW ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_BIO ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INIT_FAIL ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

BIO *BIO_new(const BIO_METHOD *method)
{
    BIO *bio = OPENSSL_zalloc(sizeof(*bio));

    if (bio == NULL) {
        BIOerr(BIO_F_BIO_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    bio->method = method;
    bio->shutdown = 1;
    bio->references = 1;

    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_BIO, bio, &bio->ex_data))
        goto err;

    bio->lock = CRYPTO_THREAD_lock_new();
    if (bio->lock == NULL) {
        BIOerr(BIO_F_BIO_NEW, ERR_R_MALLOC_FAILURE);
        CRYPTO_free_ex_data(CRYPTO_EX_INDEX_BIO, bio, &bio->ex_data);
        goto err;
    }

    if (method->create != NULL && !method->create(bio)) {
        BIOerr(BIO_F_BIO_NEW, ERR_R_INIT_FAIL);
        CRYPTO_free_ex_data(CRYPTO_EX_INDEX_BIO, bio, &bio->ex_data);
        CRYPTO_THREAD_lock_free(bio->lock);
        goto err;
    }
    if (method->create == NULL)
        bio->init = 1;

    return bio;

err:
    OPENSSL_free(bio);
    return NULL;
}