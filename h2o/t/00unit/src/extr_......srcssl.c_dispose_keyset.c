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
struct TYPE_2__ {int /*<<< orphan*/ * dec; int /*<<< orphan*/ * enc; } ;
struct st_quic_keyset_t {TYPE_1__ address_token; int /*<<< orphan*/ * cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_free_default_cid_encryptor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispose_keyset(struct st_quic_keyset_t *keyset)
{
    quicly_free_default_cid_encryptor(keyset->cid);
    keyset->cid = NULL;
    ptls_aead_free(keyset->address_token.enc);
    keyset->address_token.enc = NULL;
    ptls_aead_free(keyset->address_token.dec);
    keyset->address_token.dec = NULL;
}