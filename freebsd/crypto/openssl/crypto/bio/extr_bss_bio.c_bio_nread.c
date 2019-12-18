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
struct bio_bio_st {scalar_t__ offset; scalar_t__ size; scalar_t__ len; TYPE_1__* peer; } ;
typedef  size_t ossl_ssize_t ;
struct TYPE_6__ {struct bio_bio_st* ptr; } ;
struct TYPE_5__ {struct bio_bio_st* ptr; } ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 size_t OSSL_SSIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t bio_nread0 (TYPE_2__*,char**) ; 

__attribute__((used)) static ossl_ssize_t bio_nread(BIO *bio, char **buf, size_t num_)
{
    struct bio_bio_st *b, *peer_b;
    ossl_ssize_t num, available;

    if (num_ > OSSL_SSIZE_MAX)
        num = OSSL_SSIZE_MAX;
    else
        num = (ossl_ssize_t) num_;

    available = bio_nread0(bio, buf);
    if (num > available)
        num = available;
    if (num <= 0)
        return num;

    b = bio->ptr;
    peer_b = b->peer->ptr;

    peer_b->len -= num;
    if (peer_b->len) {
        peer_b->offset += num;
        assert(peer_b->offset <= peer_b->size);
        if (peer_b->offset == peer_b->size)
            peer_b->offset = 0;
    } else
        peer_b->offset = 0;

    return num;
}