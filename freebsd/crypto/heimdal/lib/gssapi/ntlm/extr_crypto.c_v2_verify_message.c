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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gss_buffer_t ;
typedef  int /*<<< orphan*/  RC4_KEY ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_BAD_MIC ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char*,int) ; 
 scalar_t__ v2_sign_message (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static OM_uint32
v2_verify_message(gss_buffer_t in,
		  unsigned char signkey[16],
		  RC4_KEY *sealkey,
		  uint32_t seq,
		  const unsigned char checksum[16])
{
    OM_uint32 ret;
    unsigned char out[16];

    ret = v2_sign_message(in, signkey, sealkey, seq, out);
    if (ret)
	return ret;

    if (memcmp(checksum, out, 16) != 0)
	return GSS_S_BAD_MIC;

    return GSS_S_COMPLETE;
}