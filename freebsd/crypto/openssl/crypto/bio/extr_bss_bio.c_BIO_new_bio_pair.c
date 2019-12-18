#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 long BIO_make_bio_pair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_bio () ; 
 long BIO_set_write_buf_size (int /*<<< orphan*/ *,size_t) ; 

int BIO_new_bio_pair(BIO **bio1_p, size_t writebuf1,
                     BIO **bio2_p, size_t writebuf2)
{
    BIO *bio1 = NULL, *bio2 = NULL;
    long r;
    int ret = 0;

    bio1 = BIO_new(BIO_s_bio());
    if (bio1 == NULL)
        goto err;
    bio2 = BIO_new(BIO_s_bio());
    if (bio2 == NULL)
        goto err;

    if (writebuf1) {
        r = BIO_set_write_buf_size(bio1, writebuf1);
        if (!r)
            goto err;
    }
    if (writebuf2) {
        r = BIO_set_write_buf_size(bio2, writebuf2);
        if (!r)
            goto err;
    }

    r = BIO_make_bio_pair(bio1, bio2);
    if (!r)
        goto err;
    ret = 1;

 err:
    if (ret == 0) {
        BIO_free(bio1);
        bio1 = NULL;
        BIO_free(bio2);
        bio2 = NULL;
    }

    *bio1_p = bio1;
    *bio2_p = bio2;
    return ret;
}