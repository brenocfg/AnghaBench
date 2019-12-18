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

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char*,unsigned long long) ; 

__attribute__((used)) static void get_hram(unsigned char *hram, const unsigned char *sm, const unsigned char *pk, unsigned char *playground, unsigned long long smlen)
{
  unsigned long long i;

  for (i =  0;i < 32;++i)    playground[i] = sm[i];
  for (i = 32;i < 64;++i)    playground[i] = pk[i-32];
  for (i = 64;i < smlen;++i) playground[i] = sm[i];

  crypto_hash_sha512(hram,playground,smlen);
}