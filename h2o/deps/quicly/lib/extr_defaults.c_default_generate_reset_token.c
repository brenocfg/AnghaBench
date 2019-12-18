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
struct st_quicly_default_encrypt_cid_t {int dummy; } ;
typedef  int /*<<< orphan*/  quicly_cid_encryptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  generate_reset_token (struct st_quicly_default_encrypt_cid_t*,void*,void const*) ; 

__attribute__((used)) static int default_generate_reset_token(quicly_cid_encryptor_t *_self, void *token, const void *cid)
{
    struct st_quicly_default_encrypt_cid_t *self = (void *)_self;
    generate_reset_token(self, token, cid);
    return 1;
}