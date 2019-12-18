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
typedef  int u8 ;
struct crypto_aead {int dummy; } ;
struct aead_request {unsigned int* iv; scalar_t__ assoclen; } ;

/* Variables and functions */
 unsigned int crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned int*,int) ; 
 int set_msg_len (int*,unsigned int,unsigned int) ; 

__attribute__((used)) static int format_input(u8 *info, struct aead_request *req,
			unsigned int cryptlen)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	unsigned int lp = req->iv[0];
	unsigned int l = lp + 1;
	unsigned int m;

	m = crypto_aead_authsize(aead);

	memcpy(info, req->iv, 16);

	/* format control info per RFC 3610 and
	 * NIST Special Publication 800-38C
	 */
	*info |= (8 * ((m - 2) / 2));
	if (req->assoclen)
		*info |= 64;

	return set_msg_len(info + 16 - l, cryptlen, l);
}