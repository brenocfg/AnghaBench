#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_8__ {struct TYPE_8__* next; TYPE_1__* cipher; scalar_t__ active; } ;
struct TYPE_7__ {int strength_bits; } ;
typedef  TYPE_2__ CIPHER_ORDER ;

/* Variables and functions */
 int /*<<< orphan*/  CIPHER_ORD ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int*) ; 
 int* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SSL_F_SSL_CIPHER_STRENGTH_SORT ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_cipher_apply_rule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__**,TYPE_2__**) ; 

__attribute__((used)) static int ssl_cipher_strength_sort(CIPHER_ORDER **head_p,
                                    CIPHER_ORDER **tail_p)
{
    int32_t max_strength_bits;
    int i, *number_uses;
    CIPHER_ORDER *curr;

    /*
     * This routine sorts the ciphers with descending strength. The sorting
     * must keep the pre-sorted sequence, so we apply the normal sorting
     * routine as '+' movement to the end of the list.
     */
    max_strength_bits = 0;
    curr = *head_p;
    while (curr != NULL) {
        if (curr->active && (curr->cipher->strength_bits > max_strength_bits))
            max_strength_bits = curr->cipher->strength_bits;
        curr = curr->next;
    }

    number_uses = OPENSSL_zalloc(sizeof(int) * (max_strength_bits + 1));
    if (number_uses == NULL) {
        SSLerr(SSL_F_SSL_CIPHER_STRENGTH_SORT, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    /*
     * Now find the strength_bits values actually used
     */
    curr = *head_p;
    while (curr != NULL) {
        if (curr->active)
            number_uses[curr->cipher->strength_bits]++;
        curr = curr->next;
    }
    /*
     * Go through the list of used strength_bits values in descending
     * order.
     */
    for (i = max_strength_bits; i >= 0; i--)
        if (number_uses[i] > 0)
            ssl_cipher_apply_rule(0, 0, 0, 0, 0, 0, 0, CIPHER_ORD, i, head_p,
                                  tail_p);

    OPENSSL_free(number_uses);
    return 1;
}