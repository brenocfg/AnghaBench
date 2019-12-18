#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/ * enc; } ;
struct st_quic_keyset_t {TYPE_1__ address_token; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 struct st_quic_keyset_t* update_quic_keys () ; 

ptls_aead_context_t *quic_get_address_token_encryptor(uint8_t *prefix)
{
    struct st_quic_keyset_t *keyset = update_quic_keys();
    *prefix = keyset->name;
    return keyset->address_token.enc;
}