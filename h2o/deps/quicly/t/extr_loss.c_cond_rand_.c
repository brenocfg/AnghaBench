#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {unsigned int nloss; int ntotal; } ;
struct TYPE_5__ {int bits_avail; int bits; TYPE_1__ ratio; } ;
struct TYPE_6__ {TYPE_2__ rand_; } ;
struct loss_cond_t {TYPE_3__ data; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_cipher_encrypt (int /*<<< orphan*/ *,int*,char*,int) ; 
 int /*<<< orphan*/ * ptls_cipher_new (int /*<<< orphan*/ *,int,int**) ; 
 int /*<<< orphan*/  ptls_openssl_aes128ctr ; 

__attribute__((used)) static int cond_rand_(struct loss_cond_t *cond)
{
    static ptls_cipher_context_t *c;

    if (cond->data.rand_.bits_avail == 0) {
        if (c == NULL) {
            /* use different seed for each invocation */
            static uint64_t key[2];
            c = ptls_cipher_new(&ptls_openssl_aes128ctr, 1, &key);
            ++key[0];
        }
        /* initialize next `ntotal` bits, of which `nloss` bits are set */
        cond->data.rand_.bits = 0;
        unsigned num_bits_set;
        for (num_bits_set = 0; num_bits_set != cond->data.rand_.ratio.nloss; ++num_bits_set) {
            /* choose a mask that sets a new bit */
            uint64_t mask;
            do {
                uint32_t v;
                ptls_cipher_encrypt(c, &v, "01234567", 4);
                mask = (uint64_t)1 << (v % cond->data.rand_.ratio.ntotal);
            } while ((cond->data.rand_.bits & mask) != 0);
            /* set the chosen bit */
            cond->data.rand_.bits |= mask;
        }
        cond->data.rand_.bits_avail = cond->data.rand_.ratio.ntotal;
    }

    /* return a bit, negating the value, as rand_.bits indicates the bits being lost, whereas we want to return if transmission
     * succeeds */
    return ((cond->data.rand_.bits >> --cond->data.rand_.bits_avail) & 1) == 0;
}