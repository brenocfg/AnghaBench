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
typedef  int /*<<< orphan*/  secret ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_md5_ctx_t ;

/* Variables and functions */
 int APR_MD5_DIGESTSIZE ; 
 int /*<<< orphan*/  apr_md5 (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  apr_md5_final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_md5_update (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void compute_digest(unsigned char *digest, const char *challenge,
                           const char *password)
{
  unsigned char secret[64];
  apr_size_t len = strlen(password), i;
  apr_md5_ctx_t ctx;

  /* Munge the password into a 64-byte secret. */
  memset(secret, 0, sizeof(secret));
  if (len <= sizeof(secret))
    memcpy(secret, password, len);
  else
    apr_md5(secret, password, len);

  /* Compute MD5(secret XOR opad, MD5(secret XOR ipad, challenge)),
   * where ipad is a string of 0x36 and opad is a string of 0x5c. */
  for (i = 0; i < sizeof(secret); i++)
    secret[i] ^= 0x36;
  apr_md5_init(&ctx);
  apr_md5_update(&ctx, secret, sizeof(secret));
  apr_md5_update(&ctx, challenge, strlen(challenge));
  apr_md5_final(digest, &ctx);
  for (i = 0; i < sizeof(secret); i++)
    secret[i] ^= (0x36 ^ 0x5c);
  apr_md5_init(&ctx);
  apr_md5_update(&ctx, secret, sizeof(secret));
  apr_md5_update(&ctx, digest, APR_MD5_DIGESTSIZE);
  apr_md5_final(digest, &ctx);
}