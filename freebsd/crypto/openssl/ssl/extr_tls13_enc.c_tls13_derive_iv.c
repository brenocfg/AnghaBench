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
typedef  int /*<<< orphan*/  ivlabel ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int tls13_hkdf_expand (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char const*,unsigned char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t,int) ; 

int tls13_derive_iv(SSL *s, const EVP_MD *md, const unsigned char *secret,
                    unsigned char *iv, size_t ivlen)
{
#ifdef CHARSET_EBCDIC
  static const unsigned char ivlabel[] = { 0x69, 0x76, 0x00 };
#else
  static const unsigned char ivlabel[] = "iv";
#endif

    return tls13_hkdf_expand(s, md, secret, ivlabel, sizeof(ivlabel) - 1,
                             NULL, 0, iv, ivlen, 1);
}