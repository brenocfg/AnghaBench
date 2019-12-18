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
struct st_quic_keyset_t {TYPE_1__* cid; } ;
typedef  int /*<<< orphan*/  quicly_cid_encryptor_t ;
struct TYPE_2__ {int (* generate_stateless_reset_token ) (TYPE_1__*,void*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 struct st_quic_keyset_t* find_keyset (int /*<<< orphan*/  const) ; 
 int stub1 (TYPE_1__*,void*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  update_quic_keys () ; 

__attribute__((used)) static int generate_stateless_reset_token(quicly_cid_encryptor_t *self, void *token, const void *_encrypted)
{
    const uint8_t *encrypted = _encrypted;
    struct st_quic_keyset_t *keyset;

    update_quic_keys();

    if ((keyset = find_keyset(encrypted[0])) == NULL)
        return 0;
    return keyset->cid->generate_stateless_reset_token(keyset->cid, token, encrypted + 1);
}