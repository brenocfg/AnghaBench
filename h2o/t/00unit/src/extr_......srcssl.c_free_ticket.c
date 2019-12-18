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
struct st_session_ticket_t {int /*<<< orphan*/  keybuf; int /*<<< orphan*/  hmac; int /*<<< orphan*/  cipher; } ;

/* Variables and functions */
 int EVP_CIPHER_key_length (int /*<<< orphan*/ ) ; 
 int EVP_MD_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct st_session_ticket_t*) ; 
 int /*<<< orphan*/  h2o_mem_set_secure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_ticket(struct st_session_ticket_t *ticket)
{
    int key_len = EVP_CIPHER_key_length(ticket->cipher), block_size = EVP_MD_block_size(ticket->hmac);
    h2o_mem_set_secure(ticket->keybuf, 0, key_len + block_size);
    free(ticket);
}