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
typedef  int /*<<< orphan*/  keylabel ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int tls13_hkdf_expand (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char const*,unsigned char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t,int) ; 

int tls13_derive_key(SSL *s, const EVP_MD *md, const unsigned char *secret,
                     unsigned char *key, size_t keylen)
{
#ifdef CHARSET_EBCDIC
  static const unsigned char keylabel[] ={ 0x6B, 0x65, 0x79, 0x00 };
#else
  static const unsigned char keylabel[] = "key";
#endif

    return tls13_hkdf_expand(s, md, secret, keylabel, sizeof(keylabel) - 1,
                             NULL, 0, key, keylen, 1);
}