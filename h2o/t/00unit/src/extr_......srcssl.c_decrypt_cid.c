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
typedef  int /*<<< orphan*/  quicly_cid_plaintext_t ;
typedef  int /*<<< orphan*/  quicly_cid_encryptor_t ;
struct TYPE_2__ {size_t (* decrypt_cid ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 struct st_quic_keyset_t* find_keyset (int /*<<< orphan*/  const) ; 
 size_t stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  update_quic_keys () ; 

__attribute__((used)) static size_t decrypt_cid(quicly_cid_encryptor_t *self, quicly_cid_plaintext_t *plaintext, const void *_encrypted, size_t len)
{
    const uint8_t *encrypted = _encrypted;
    struct st_quic_keyset_t *keyset;

    update_quic_keys();

    if ((keyset = find_keyset(encrypted[0])) == NULL)
        return SIZE_MAX;
    if ((len = keyset->cid->decrypt_cid(keyset->cid, plaintext, encrypted + 1, len != 0 ? len - 1 : 0)) == SIZE_MAX)
        return SIZE_MAX;
    return 1 + len;
}