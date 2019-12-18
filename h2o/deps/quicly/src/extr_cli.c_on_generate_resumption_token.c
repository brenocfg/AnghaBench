#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_generate_resumption_token_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
typedef  int /*<<< orphan*/  quicly_address_token_plaintext_t ;
struct TYPE_6__ {int /*<<< orphan*/  off; } ;
typedef  TYPE_1__ ptls_buffer_t ;
struct TYPE_8__ {int /*<<< orphan*/  enc; } ;
struct TYPE_7__ {int /*<<< orphan*/  random_bytes; } ;

/* Variables and functions */
 TYPE_5__ address_token_aead ; 
 int quicly_encrypt_address_token (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__ tlsctx ; 

__attribute__((used)) static int on_generate_resumption_token(quicly_generate_resumption_token_t *self, quicly_conn_t *conn, ptls_buffer_t *buf,
                                        quicly_address_token_plaintext_t *token)
{
    return quicly_encrypt_address_token(tlsctx.random_bytes, address_token_aead.enc, buf, buf->off, token);
}