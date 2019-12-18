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
typedef  int /*<<< orphan*/  sigature ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  RC4_KEY ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_S_UNAVAILABLE ; 
 int RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  _krb5_crc_init_table () ; 
 int _krb5_crc_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_le_uint32 (int,unsigned char*) ; 

__attribute__((used)) static OM_uint32
v1_sign_message(gss_buffer_t in,
		RC4_KEY *signkey,
		uint32_t seq,
		unsigned char out[16])
{
    unsigned char sigature[12];
    uint32_t crc;

    _krb5_crc_init_table();
    crc = _krb5_crc_update(in->value, in->length, 0);

    encode_le_uint32(0, &sigature[0]);
    encode_le_uint32(crc, &sigature[4]);
    encode_le_uint32(seq, &sigature[8]);

    encode_le_uint32(1, out); /* version */
    RC4(signkey, sizeof(sigature), sigature, out + 4);

    if (RAND_bytes(out + 4, 4) != 1)
	return GSS_S_UNAVAILABLE;

    return 0;
}