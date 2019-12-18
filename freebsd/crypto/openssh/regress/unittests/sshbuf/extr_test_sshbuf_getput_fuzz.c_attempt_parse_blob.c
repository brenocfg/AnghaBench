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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
typedef  struct sshbuf EC_KEY ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  EC_KEY_free (struct sshbuf*) ; 
 struct sshbuf* EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_X9_62_prime256v1 ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_get_bignum1 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_get_bignum2 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_get_eckey (struct sshbuf*,struct sshbuf*) ; 
 scalar_t__ sshbuf_get_string (struct sshbuf*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  sshbuf_get_u16 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_get_u32 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_get_u64 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_get_u8 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_put (struct sshbuf*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
attempt_parse_blob(u_char *blob, size_t len)
{
	struct sshbuf *p1;
	BIGNUM *bn;
#if defined(OPENSSL_HAS_ECC) && defined(OPENSSL_HAS_NISTP256)
	EC_KEY *eck;
#endif
	u_char *s;
	size_t l;
	u_int8_t u8;
	u_int16_t u16;
	u_int32_t u32;
	u_int64_t u64;

	p1 = sshbuf_new();
	ASSERT_PTR_NE(p1, NULL);
	ASSERT_INT_EQ(sshbuf_put(p1, blob, len), 0);
	sshbuf_get_u8(p1, &u8);
	sshbuf_get_u16(p1, &u16);
	sshbuf_get_u32(p1, &u32);
	sshbuf_get_u64(p1, &u64);
	if (sshbuf_get_string(p1, &s, &l) == 0) {
		bzero(s, l);
		free(s);
	}
	bn = BN_new();
	sshbuf_get_bignum1(p1, bn);
	BN_clear_free(bn);
	bn = BN_new();
	sshbuf_get_bignum2(p1, bn);
	BN_clear_free(bn);
#if defined(OPENSSL_HAS_ECC) && defined(OPENSSL_HAS_NISTP256)
	eck = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
	ASSERT_PTR_NE(eck, NULL);
	sshbuf_get_eckey(p1, eck);
	EC_KEY_free(eck);
#endif
	sshbuf_free(p1);
}