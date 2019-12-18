#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_12__ {int active; struct TYPE_12__* prev; struct TYPE_12__* next; TYPE_1__* cipher; } ;
struct TYPE_11__ {int strength_bits; char* name; int algorithm_mkey; int algorithm_auth; int algorithm_enc; int algorithm_mac; int min_tls; int algo_strength; int id; } ;
typedef  TYPE_1__ SSL_CIPHER ;
typedef  TYPE_2__ CIPHER_ORDER ;

/* Variables and functions */
 int CIPHER_ADD ; 
 int CIPHER_BUMP ; 
 int CIPHER_DEL ; 
 int CIPHER_KILL ; 
 int CIPHER_ORD ; 
 int SSL_DEFAULT_MASK ; 
 int SSL_STRONG_MASK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ll_append_head (TYPE_2__**,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  ll_append_tail (TYPE_2__**,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ssl_cipher_apply_rule(uint32_t cipher_id, uint32_t alg_mkey,
                                  uint32_t alg_auth, uint32_t alg_enc,
                                  uint32_t alg_mac, int min_tls,
                                  uint32_t algo_strength, int rule,
                                  int32_t strength_bits, CIPHER_ORDER **head_p,
                                  CIPHER_ORDER **tail_p)
{
    CIPHER_ORDER *head, *tail, *curr, *next, *last;
    const SSL_CIPHER *cp;
    int reverse = 0;

#ifdef CIPHER_DEBUG
    fprintf(stderr,
            "Applying rule %d with %08x/%08x/%08x/%08x/%08x %08x (%d)\n",
            rule, alg_mkey, alg_auth, alg_enc, alg_mac, min_tls,
            algo_strength, strength_bits);
#endif

    if (rule == CIPHER_DEL || rule == CIPHER_BUMP)
        reverse = 1;            /* needed to maintain sorting between currently
                                 * deleted ciphers */

    head = *head_p;
    tail = *tail_p;

    if (reverse) {
        next = tail;
        last = head;
    } else {
        next = head;
        last = tail;
    }

    curr = NULL;
    for (;;) {
        if (curr == last)
            break;

        curr = next;

        if (curr == NULL)
            break;

        next = reverse ? curr->prev : curr->next;

        cp = curr->cipher;

        /*
         * Selection criteria is either the value of strength_bits
         * or the algorithms used.
         */
        if (strength_bits >= 0) {
            if (strength_bits != cp->strength_bits)
                continue;
        } else {
#ifdef CIPHER_DEBUG
            fprintf(stderr,
                    "\nName: %s:\nAlgo = %08x/%08x/%08x/%08x/%08x Algo_strength = %08x\n",
                    cp->name, cp->algorithm_mkey, cp->algorithm_auth,
                    cp->algorithm_enc, cp->algorithm_mac, cp->min_tls,
                    cp->algo_strength);
#endif
            if (cipher_id != 0 && (cipher_id != cp->id))
                continue;
            if (alg_mkey && !(alg_mkey & cp->algorithm_mkey))
                continue;
            if (alg_auth && !(alg_auth & cp->algorithm_auth))
                continue;
            if (alg_enc && !(alg_enc & cp->algorithm_enc))
                continue;
            if (alg_mac && !(alg_mac & cp->algorithm_mac))
                continue;
            if (min_tls && (min_tls != cp->min_tls))
                continue;
            if ((algo_strength & SSL_STRONG_MASK)
                && !(algo_strength & SSL_STRONG_MASK & cp->algo_strength))
                continue;
            if ((algo_strength & SSL_DEFAULT_MASK)
                && !(algo_strength & SSL_DEFAULT_MASK & cp->algo_strength))
                continue;
        }

#ifdef CIPHER_DEBUG
        fprintf(stderr, "Action = %d\n", rule);
#endif

        /* add the cipher if it has not been added yet. */
        if (rule == CIPHER_ADD) {
            /* reverse == 0 */
            if (!curr->active) {
                ll_append_tail(&head, curr, &tail);
                curr->active = 1;
            }
        }
        /* Move the added cipher to this location */
        else if (rule == CIPHER_ORD) {
            /* reverse == 0 */
            if (curr->active) {
                ll_append_tail(&head, curr, &tail);
            }
        } else if (rule == CIPHER_DEL) {
            /* reverse == 1 */
            if (curr->active) {
                /*
                 * most recently deleted ciphersuites get best positions for
                 * any future CIPHER_ADD (note that the CIPHER_DEL loop works
                 * in reverse to maintain the order)
                 */
                ll_append_head(&head, curr, &tail);
                curr->active = 0;
            }
        } else if (rule == CIPHER_BUMP) {
            if (curr->active)
                ll_append_head(&head, curr, &tail);
        } else if (rule == CIPHER_KILL) {
            /* reverse == 0 */
            if (head == curr)
                head = curr->next;
            else
                curr->prev->next = curr->next;
            if (tail == curr)
                tail = curr->prev;
            curr->active = 0;
            if (curr->next != NULL)
                curr->next->prev = curr->prev;
            if (curr->prev != NULL)
                curr->prev->next = curr->next;
            curr->next = NULL;
            curr->prev = NULL;
        }
    }

    *head_p = head;
    *tail_p = tail;
}