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
 int /*<<< orphan*/  cf_sha224 ; 
 int /*<<< orphan*/  cf_sha224_digest_final ; 
 int /*<<< orphan*/  vector (int /*<<< orphan*/  const*,char*,int,char*,int) ; 
 int /*<<< orphan*/  vector_abc_final (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vector_length (int /*<<< orphan*/  const*,int,char*,int) ; 

__attribute__((used)) static void test_sha224(void)
{
  const cf_chash *h = &cf_sha224;
  vector(h, "", 0, "\xd1\x4a\x02\x8c\x2a\x3a\x2b\xc9\x47\x61\x02\xbb\x28\x82\x34\xc4\x15\xa2\xb0\x1f\x82\x8e\xa6\x2a\xc5\xb3\xe4\x2f", 28);
  vector(h, "abc", 3, "\x23\x09\x7d\x22\x34\x05\xd8\x22\x86\x42\xa4\x77\xbd\xa2\x55\xb3\x2a\xad\xbc\xe4\xbd\xa0\xb3\xf7\xe3\x6c\x9d\xa7", 28);
  vector(h, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56,
         "\x75\x38\x8b\x16\x51\x27\x76\xcc\x5d\xba\x5d\xa1\xfd\x89\x01\x50\xb0\xc6\x45\x5c\xb4\xf5\x8b\x19\x52\x52\x25\x25", 28);
  vector(h, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", 112,
         "\xc9\x7c\xa9\xa5\x59\x85\x0c\xe9\x7a\x04\xa9\x6d\xef\x6d\x99\xa9\xe0\xe0\xe2\xab\x14\xe6\xb8\xdf\x26\x5f\xc0\xb3", 28);
  
  /* Check that incremental interface produces correct results. */
  vector_abc_final(h, cf_sha224_digest_final, "\x23\x09\x7d\x22\x34\x05\xd8\x22\x86\x42\xa4\x77\xbd\xa2\x55\xb3\x2a\xad\xbc\xe4\xbd\xa0\xb3\xf7\xe3\x6c\x9d\xa7", 28);

  vector_length(h, 1024, "\x08\x2c\x80\x5b\x6f\x85\xde\x0e\xdf\xa8\x51\xa0\x1f\xe6\x4f\x64\x85\x16\x48\xae\xfc\xc1\xd4\x52\x4e\xf8\x36\xe7", 28);
}