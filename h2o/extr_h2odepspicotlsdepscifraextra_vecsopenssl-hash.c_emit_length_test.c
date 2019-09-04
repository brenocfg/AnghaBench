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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal (int /*<<< orphan*/ *,size_t*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,size_t*,unsigned int) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printhex (size_t*,size_t) ; 

__attribute__((used)) static void emit_length_test(const char *name, const EVP_MD *h, size_t max)
{
  EVP_MD_CTX outer, inner;
  EVP_DigestInit(&outer, h);
  uint8_t digest[EVP_MAX_MD_SIZE];
  unsigned int digestlen;

  for (size_t n = 0; n < max; n++)
  {
    EVP_DigestInit(&inner, h);
    for (size_t i = 0; i < n; i++)
    {
      uint8_t byte = n & 0xff;
      EVP_DigestUpdate(&inner, &byte, 1);
    }
    digestlen = sizeof digest;
    EVP_DigestFinal(&inner, digest, &digestlen);

    EVP_DigestUpdate(&outer, digest, digestlen);
  }

  digestlen = sizeof digest;
  EVP_DigestFinal(&outer, digest, &digestlen);

  printf("%s(%zu) = ", name, max);
  printhex(digest, (size_t) digestlen);
  printf("\n");
}