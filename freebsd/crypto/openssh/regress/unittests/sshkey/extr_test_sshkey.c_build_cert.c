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
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int dummy; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSH2_CERT_TYPE_USER ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_opt (struct sshbuf*,char*,char*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_ptr (struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_put_cstring (struct sshbuf*,char const*) ; 
 int /*<<< orphan*/  sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sshbuf_put_stringb (struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_put_u32 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_put_u64 (struct sshbuf*,int) ; 
 int /*<<< orphan*/  sshbuf_putb (struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_skip_string (struct sshbuf*) ; 
 int /*<<< orphan*/  sshkey_putb (struct sshkey const*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshkey_putb_plain (struct sshkey const*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshkey_sign (struct sshkey const*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
build_cert(struct sshbuf *b, const struct sshkey *k, const char *type,
    const struct sshkey *sign_key, const struct sshkey *ca_key,
    const char *sig_alg)
{
	struct sshbuf *ca_buf, *pk, *principals, *critopts, *exts;
	u_char *sigblob;
	size_t siglen;

	ca_buf = sshbuf_new();
	ASSERT_PTR_NE(ca_buf, NULL);
	ASSERT_INT_EQ(sshkey_putb(ca_key, ca_buf), 0);

	/*
	 * Get the public key serialisation by rendering the key and skipping
	 * the type string. This is a bit of a hack :/
	 */
	pk = sshbuf_new();
	ASSERT_PTR_NE(pk, NULL);
	ASSERT_INT_EQ(sshkey_putb_plain(k, pk), 0);
	ASSERT_INT_EQ(sshbuf_skip_string(pk), 0);

	principals = sshbuf_new();
	ASSERT_PTR_NE(principals, NULL);
	ASSERT_INT_EQ(sshbuf_put_cstring(principals, "gsamsa"), 0);
	ASSERT_INT_EQ(sshbuf_put_cstring(principals, "gregor"), 0);

	critopts = sshbuf_new();
	ASSERT_PTR_NE(critopts, NULL);
	put_opt(critopts, "force-command", "/usr/local/bin/nethack");
	put_opt(critopts, "source-address", "192.168.0.0/24,127.0.0.1,::1");

	exts = sshbuf_new();
	ASSERT_PTR_NE(exts, NULL);
	put_opt(critopts, "permit-X11-forwarding", NULL);

	ASSERT_INT_EQ(sshbuf_put_cstring(b, type), 0);
	ASSERT_INT_EQ(sshbuf_put_cstring(b, "noncenoncenonce!"), 0); /* nonce */
	ASSERT_INT_EQ(sshbuf_putb(b, pk), 0); /* public key serialisation */
	ASSERT_INT_EQ(sshbuf_put_u64(b, 1234), 0); /* serial */
	ASSERT_INT_EQ(sshbuf_put_u32(b, SSH2_CERT_TYPE_USER), 0); /* type */
	ASSERT_INT_EQ(sshbuf_put_cstring(b, "gregor"), 0); /* key ID */
	ASSERT_INT_EQ(sshbuf_put_stringb(b, principals), 0); /* principals */
	ASSERT_INT_EQ(sshbuf_put_u64(b, 0), 0); /* start */
	ASSERT_INT_EQ(sshbuf_put_u64(b, 0xffffffffffffffffULL), 0); /* end */
	ASSERT_INT_EQ(sshbuf_put_stringb(b, critopts), 0); /* options */
	ASSERT_INT_EQ(sshbuf_put_stringb(b, exts), 0); /* extensions */
	ASSERT_INT_EQ(sshbuf_put_string(b, NULL, 0), 0); /* reserved */
	ASSERT_INT_EQ(sshbuf_put_stringb(b, ca_buf), 0); /* signature key */
	ASSERT_INT_EQ(sshkey_sign(sign_key, &sigblob, &siglen,
	    sshbuf_ptr(b), sshbuf_len(b), sig_alg, 0), 0);
	ASSERT_INT_EQ(sshbuf_put_string(b, sigblob, siglen), 0); /* signature */

	free(sigblob);
	sshbuf_free(ca_buf);
	sshbuf_free(exts);
	sshbuf_free(critopts);
	sshbuf_free(principals);
	sshbuf_free(pk);
}