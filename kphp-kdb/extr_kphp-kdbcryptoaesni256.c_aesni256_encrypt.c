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

__attribute__((used)) static void aesni256_encrypt (unsigned char *ctx, const unsigned char *in, unsigned char *out) {
  void *p1, *p2;
  asm volatile (
      "movdqu (%2), %%xmm1\n\t"
      "pxor (%3), %%xmm1\n\t"
      "aesenc 0x10(%3), %%xmm1\n\t"
      "aesenc 0x20(%3), %%xmm1\n\t"
      "aesenc 0x30(%3), %%xmm1\n\t"
      "aesenc 0x40(%3), %%xmm1\n\t"
      "aesenc 0x50(%3), %%xmm1\n\t"
      "aesenc 0x60(%3), %%xmm1\n\t"
      "aesenc 0x70(%3), %%xmm1\n\t"
      "aesenc 0x80(%3), %%xmm1\n\t"
      "aesenc 0x90(%3), %%xmm1\n\t"
      "aesenc 0xa0(%3), %%xmm1\n\t"
      "aesenc 0xb0(%3), %%xmm1\n\t"
      "aesenc 0xc0(%3), %%xmm1\n\t"
      "aesenc 0xd0(%3), %%xmm1\n\t"
      "aesenclast 0xe0(%3), %%xmm1\n\t"
      "movdqu %%xmm1, (%4)\n\t"
    : "=r" (p1), "=r" (p2)
    : "0r" (in), "r" (ctx), "1r" (out)
    : "%xmm1", "memory"
  );
}