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
typedef  int uint32_t ;
struct ead_msg_encrypted {unsigned int pad; void** hash; void* iv; } ;
struct ead_msg {void* len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,void*,int) ; 
 struct ead_msg_encrypted* EAD_DATA (struct ead_msg*,int /*<<< orphan*/ ) ; 
 unsigned int EAD_ENC_PAD ; 
 int /*<<< orphan*/  aes_enc_ctx ; 
 int ead_get_tx_iv () ; 
 int /*<<< orphan*/  ead_hash_message (struct ead_msg_encrypted*,int*,int) ; 
 struct ead_msg_encrypted* enc ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  rijndaelEncrypt (int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

void
ead_encrypt_message(struct ead_msg *msg, unsigned int len)
{
	struct ead_msg_encrypted *enc = EAD_DATA(msg, enc);
	unsigned char *data = (unsigned char *) enc;
	uint32_t hash[5];
	int enclen, i;

	len += sizeof(struct ead_msg_encrypted);
	enc->pad = (EAD_ENC_PAD - (len % EAD_ENC_PAD)) % EAD_ENC_PAD;
	enclen = len + enc->pad;
	msg->len = htonl(enclen);
	enc->iv = htonl(ead_get_tx_iv());

	ead_hash_message(enc, hash, enclen);
	for (i = 0; i < 5; i++)
		enc->hash[i] = htonl(hash[i]);
	DEBUG(2, "SHA1 generate (0x%08x), len=%d\n", enc->hash[0], enclen);

	while (enclen > 0) {
		rijndaelEncrypt(aes_enc_ctx, data, data);
		data += 16;
		enclen -= 16;
	}
}