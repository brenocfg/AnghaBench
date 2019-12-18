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
 int /*<<< orphan*/  cf_sha3_256 ; 
 int /*<<< orphan*/  cf_sha3_256_digest_final ; 
 int /*<<< orphan*/  vector (int /*<<< orphan*/  const*,char*,int,char*,int) ; 
 int /*<<< orphan*/  vector_abc_final (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vector_length (int /*<<< orphan*/  const*,int,char*,int) ; 

__attribute__((used)) static void test_sha3_256(void)
{
  const cf_chash *H = &cf_sha3_256;
  vector(H, "", 0,
         "\xa7\xff\xc6\xf8\xbf\x1e\xd7\x66\x51\xc1\x47\x56\xa0\x61\xd6\x62\xf5\x80\xff\x4d\xe4\x3b\x49\xfa\x82\xd8\x0a\x4b\x80\xf8\x43\x4a", 32);
  vector(H, "abc", 3,
         "\x3a\x98\x5d\xa7\x4f\xe2\x25\xb2\x04\x5c\x17\x2d\x6b\xd3\x90\xbd\x85\x5f\x08\x6e\x3e\x9d\x52\x5b\x46\xbf\xe2\x45\x11\x43\x15\x32", 32);
  vector(H, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56,
         "\x41\xc0\xdb\xa2\xa9\xd6\x24\x08\x49\x10\x03\x76\xa8\x23\x5e\x2c\x82\xe1\xb9\x99\x8a\x99\x9e\x21\xdb\x32\xdd\x97\x49\x6d\x33\x76", 32);
  vector(H, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", 112,
         "\x91\x6f\x60\x61\xfe\x87\x97\x41\xca\x64\x69\xb4\x39\x71\xdf\xdb\x28\xb1\xa3\x2d\xc3\x6c\xb3\x25\x4e\x81\x2b\xe2\x7a\xad\x1d\x18", 32);

  vector_abc_final(H, cf_sha3_256_digest_final,
                   "\x3a\x98\x5d\xa7\x4f\xe2\x25\xb2\x04\x5c\x17\x2d\x6b\xd3\x90\xbd\x85\x5f\x08\x6e\x3e\x9d\x52\x5b\x46\xbf\xe2\x45\x11\x43\x15\x32", 32);

  vector_length(H, 1024, "\xf7\xed\xf7\x2b\x34\x8c\xb4\xab\x5e\xe7\x4f\x6c\xae\xaf\x11\xad\xe2\x2f\x04\x65\x84\x8e\x5c\xaa\x14\x38\x7f\xd4\xeb\xdb\x9d\x70", 32);
}