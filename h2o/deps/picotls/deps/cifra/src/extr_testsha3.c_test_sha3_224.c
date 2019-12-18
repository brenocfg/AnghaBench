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
typedef  int /*<<< orphan*/  cf_chash ;

/* Variables and functions */
 int /*<<< orphan*/  cf_sha3_224 ; 
 int /*<<< orphan*/  cf_sha3_224_digest_final ; 
 int /*<<< orphan*/  vector (int /*<<< orphan*/  const*,char*,int,char*,int) ; 
 int /*<<< orphan*/  vector_abc_final (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vector_length (int /*<<< orphan*/  const*,int,char*,int) ; 

__attribute__((used)) static void test_sha3_224(void)
{
  const cf_chash *H = &cf_sha3_224;
  vector(H, "", 0,
         "\x6b\x4e\x03\x42\x36\x67\xdb\xb7\x3b\x6e\x15\x45\x4f\x0e\xb1\xab\xd4\x59\x7f\x9a\x1b\x07\x8e\x3f\x5b\x5a\x6b\xc7", 28);
  vector(H, "abc", 3,
         "\xe6\x42\x82\x4c\x3f\x8c\xf2\x4a\xd0\x92\x34\xee\x7d\x3c\x76\x6f\xc9\xa3\xa5\x16\x8d\x0c\x94\xad\x73\xb4\x6f\xdf", 28);
  vector(H, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56,
         "\x8a\x24\x10\x8b\x15\x4a\xda\x21\xc9\xfd\x55\x74\x49\x44\x79\xba\x5c\x7e\x7a\xb7\x6e\xf2\x64\xea\xd0\xfc\xce\x33", 28);
  vector(H, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", 112,
         "\x54\x3e\x68\x68\xe1\x66\x6c\x1a\x64\x36\x30\xdf\x77\x36\x7a\xe5\xa6\x2a\x85\x07\x0a\x51\xc1\x4c\xbf\x66\x5c\xbc", 28);

  /* Artificial exercise for len(msg) = rate_bytes - 1 codepath */
  vector(H, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 143,
         "\x73\xb1\xb2\x2b\x54\xf5\x15\xf6\x26\xa6\xab\xdd\xe6\xaf\x25\xcd\x48\x01\xdc\x6e\x9d\xc7\xfa\x3f\x77\xe1\xc1\x22", 28);

  vector_abc_final(H, cf_sha3_224_digest_final,
                   "\xe6\x42\x82\x4c\x3f\x8c\xf2\x4a\xd0\x92\x34\xee\x7d\x3c\x76\x6f\xc9\xa3\xa5\x16\x8d\x0c\x94\xad\x73\xb4\x6f\xdf", 28);

  vector_length(H, 1024, "\xf2\x54\xf3\x67\x6d\xc6\xc0\x0f\x2f\xee\x50\x59\x07\x62\x8b\x0d\x5b\x9e\xdf\xf8\xe8\xc2\x9e\x9b\xa7\xd6\x05\xdd", 28);
}