#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {unsigned char* value; int length; } ;
typedef  int /*<<< orphan*/  RC4_KEY ;
typedef  int /*<<< orphan*/  OM_uint32 ;
typedef  int /*<<< orphan*/  HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  GSS_S_COMPLETE ; 
 int /*<<< orphan*/  GSS_S_FAILURE ; 
 int /*<<< orphan*/  HMAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HMAC_CTX_new () ; 
 int /*<<< orphan*/  HMAC_Final (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  HMAC_Init_ex (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HMAC_Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  encode_le_uint32 (int,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OM_uint32
v2_sign_message(gss_buffer_t in,
		unsigned char signkey[16],
		RC4_KEY *sealkey,
		uint32_t seq,
		unsigned char out[16])
{
    unsigned char hmac[16];
    unsigned int hmaclen;
    HMAC_CTX *c;

    c = HMAC_CTX_new();
    if (c == NULL)
	return GSS_S_FAILURE;
    HMAC_Init_ex(c, signkey, 16, EVP_md5(), NULL);

    encode_le_uint32(seq, hmac);
    HMAC_Update(c, hmac, 4);
    HMAC_Update(c, in->value, in->length);
    HMAC_Final(c, hmac, &hmaclen);
    HMAC_CTX_free(c);

    encode_le_uint32(1, &out[0]);
    if (sealkey)
	RC4(sealkey, 8, hmac, &out[4]);
    else
	memcpy(&out[4], hmac, 8);

    memset(&out[12], 0, 4);

    return GSS_S_COMPLETE;
}