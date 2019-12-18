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
 int /*<<< orphan*/  cf_sha1 ; 
 int /*<<< orphan*/  cf_sha1_digest_final ; 
 int /*<<< orphan*/  vector (int /*<<< orphan*/  const*,char*,int,char*,int) ; 
 int /*<<< orphan*/  vector_abc_final (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vector_length (int /*<<< orphan*/  const*,int,char*,int) ; 

__attribute__((used)) static void test_sha1(void)
{
  const cf_chash *h = &cf_sha1;
  vector(h, "", 0, "\xda\x39\xa3\xee\x5e\x6b\x4b\x0d\x32\x55\xbf\xef\x95\x60\x18\x90\xaf\xd8\x07\x09", 20);
  vector(h, "abc", 3, "\xa9\x99\x3e\x36\x47\x06\x81\x6a\xba\x3e\x25\x71\x78\x50\xc2\x6c\x9c\xd0\xd8\x9d", 20);
  vector(h, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56,
         "\x84\x98\x3e\x44\x1c\x3b\xd2\x6e\xba\xae\x4a\xa1\xf9\x51\x29\xe5\xe5\x46\x70\xf1", 20);
  vector(h, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", 112,
         "\xa4\x9b\x24\x46\xa0\x2c\x64\x5b\xf4\x19\xf9\x95\xb6\x70\x91\x25\x3a\x04\xa2\x59", 20);

  vector_abc_final(h, cf_sha1_digest_final, "\xa9\x99\x3e\x36\x47\x06\x81\x6a\xba\x3e\x25\x71\x78\x50\xc2\x6c\x9c\xd0\xd8\x9d", 20);

  vector_length(h, 1024, "\x15\x53\x65\xcf\x77\xee\xd4\x8f\x46\xe2\x55\xc7\xdd\xdf\xfd\x0a\xf6\x99\x88\xbe", 20);
}