#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_session_ticket_t {int /*<<< orphan*/  hmac; int /*<<< orphan*/  cipher; int /*<<< orphan*/  keybuf; int /*<<< orphan*/ * name; } ;
struct st_quic_keyset_t {int dummy; } ;
struct TYPE_8__ {scalar_t__ size; struct st_quic_keyset_t* entries; } ;
struct TYPE_7__ {unsigned int generation; TYPE_4__ keys; } ;
struct TYPE_5__ {scalar_t__ size; struct st_session_ticket_t** entries; } ;
struct TYPE_6__ {unsigned int generation; int /*<<< orphan*/  rwlock; TYPE_1__ tickets; } ;

/* Variables and functions */
 scalar_t__ EVP_CIPHER_key_length (int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_MD_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dispose_keyset (struct st_quic_keyset_t*) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  init_keyset (struct st_quic_keyset_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__ quic_keys ; 
 TYPE_2__ session_tickets ; 

__attribute__((used)) static struct st_quic_keyset_t *update_quic_keys(void)
{
    unsigned new_generation;

    while ((new_generation = session_tickets.generation) != quic_keys.generation) {
        /* we need to update. first, release all entries from quic_keys */
        while (quic_keys.keys.size != 0)
            dispose_keyset(quic_keys.keys.entries + --quic_keys.keys.size);

        /* build quic_keys while taking the read lock */
        pthread_rwlock_rdlock(&session_tickets.rwlock);
        assert(session_tickets.tickets.size != 0);
        h2o_vector_reserve(NULL, &quic_keys.keys, session_tickets.tickets.size);
        for (; quic_keys.keys.size != session_tickets.tickets.size; ++quic_keys.keys.size) {
            struct st_session_ticket_t *ticket = session_tickets.tickets.entries[quic_keys.keys.size];
            init_keyset(quic_keys.keys.entries + quic_keys.keys.size, ticket->name[0],
                        ptls_iovec_init(ticket->keybuf, EVP_CIPHER_key_length(ticket->cipher) + EVP_MD_block_size(ticket->hmac)));
        }
        pthread_rwlock_unlock(&session_tickets.rwlock);

        /* update our counter */
        quic_keys.generation = new_generation;
    }

    return quic_keys.keys.entries;
}