#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_session_ticket_t {scalar_t__ not_before; int /*<<< orphan*/  hmac; int /*<<< orphan*/  cipher; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {size_t size; struct st_session_ticket_t** entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  rwlock; TYPE_2__ tickets; } ;
typedef  int /*<<< orphan*/  HMAC_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  EVP_MAX_IV_LENGTH ; 
 int /*<<< orphan*/  EVP_MD_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int HMAC_Init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_bytes (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 struct st_session_ticket_t* find_ticket_for_encryption (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  free_ticket (struct st_session_ticket_t*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct st_session_ticket_t* new_ticket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_ticket_get_cipher_key (struct st_session_ticket_t*) ; 
 int /*<<< orphan*/  session_ticket_get_hmac_key (struct st_session_ticket_t*) ; 
 TYPE_1__ session_tickets ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ticket_key_callback(unsigned char *key_name, unsigned char *iv, EVP_CIPHER_CTX *ctx, HMAC_CTX *hctx, int enc)
{
    int ret;
    pthread_rwlock_rdlock(&session_tickets.rwlock);

    if (enc) {
        RAND_bytes(iv, EVP_MAX_IV_LENGTH);
        struct st_session_ticket_t *ticket = find_ticket_for_encryption(&session_tickets.tickets, time(NULL)), *temp_ticket = NULL;
        if (ticket != NULL) {
        } else {
            /* create a dummy ticket and use (this is the only way to continue the handshake; contrary to the man pages, OpenSSL
             * crashes if we return zero */
            ticket = temp_ticket = new_ticket(EVP_aes_256_cbc(), EVP_sha256(), 0, UINT64_MAX, 1);
        }
        memcpy(key_name, ticket->name, sizeof(ticket->name));
        ret = EVP_EncryptInit_ex(ctx, ticket->cipher, NULL, session_ticket_get_cipher_key(ticket), iv);
        assert(ret);
        ret = HMAC_Init_ex(hctx, session_ticket_get_hmac_key(ticket), EVP_MD_block_size(ticket->hmac), ticket->hmac, NULL);
        assert(ret);
        if (temp_ticket != NULL)
            free_ticket(ticket);
        ret = 1;
    } else {
        struct st_session_ticket_t *ticket;
        size_t i;
        for (i = 0; i != session_tickets.tickets.size; ++i) {
            ticket = session_tickets.tickets.entries[i];
            if (memcmp(ticket->name, key_name, sizeof(ticket->name)) == 0)
                goto Found;
        }
        /* not found */
        ret = 0;
        goto Exit;
    Found:
        ret = EVP_DecryptInit_ex(ctx, ticket->cipher, NULL, session_ticket_get_cipher_key(ticket), iv);
        assert(ret);
        ret = HMAC_Init_ex(hctx, session_ticket_get_hmac_key(ticket), EVP_MD_block_size(ticket->hmac), ticket->hmac, NULL);
        assert(ret);
        /* Request renewal if the youngest key is active */
        if (i != 0 && session_tickets.tickets.entries[i - 1]->not_before <= time(NULL))
            ret = 2;
        else
            ret = 1;
    }

Exit:
    pthread_rwlock_unlock(&session_tickets.rwlock);
    return ret;
}