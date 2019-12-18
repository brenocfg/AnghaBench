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
typedef  char uint8_t ;
struct mbuf {int dummy; } ;
struct krb5_key_state {char* ks_key; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  MD5Update_int ; 
 int /*<<< orphan*/  arcfour_hmac (char*,char*,int,char*) ; 
 int /*<<< orphan*/  m_apply (struct mbuf*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_copyback (struct mbuf*,size_t,size_t,char*) ; 

__attribute__((used)) static void
arcfour_checksum(const struct krb5_key_state *ks, int usage,
    struct mbuf *inout, size_t skip, size_t inlen, size_t outlen)
{
	MD5_CTX md5;
	uint8_t Ksign[16];
	uint8_t t[4];
	uint8_t sgn_cksum[16];

	arcfour_hmac(ks->ks_key, "signaturekey", 13, Ksign);

	t[0] = usage >> 0;
	t[1] = usage >> 8;
	t[2] = usage >> 16;
	t[3] = usage >> 24;

	MD5Init(&md5);
	MD5Update(&md5, t, 4);
	m_apply(inout, skip, inlen, MD5Update_int, &md5);
	MD5Final(sgn_cksum, &md5);
	
	arcfour_hmac(Ksign, sgn_cksum, 16, sgn_cksum);
	m_copyback(inout, skip + inlen, outlen, sgn_cksum);
}