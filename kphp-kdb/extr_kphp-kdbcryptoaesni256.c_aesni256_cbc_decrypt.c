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
struct aesni256_ctx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void aesni256_cbc_decrypt (struct aesni256_ctx *ctx, const unsigned char *in, unsigned char *out, int size, unsigned char iv[16]) {
  void *p1, *p2;
  if (size < 16) {
    return;
  }
  asm volatile (
      "movdqu (%5), %%xmm1\n\t"
      "1:\n\t"
      "subl $0x10, %3\n\t"
      "movdqu (%4), %%xmm2\n\t"
      "pxor 0xe0(%6), %%xmm2\n\t"
      "aesdec 0xd0(%6), %%xmm2\n\t"
      "aesdec 0xc0(%6), %%xmm2\n\t"
      "aesdec 0xb0(%6), %%xmm2\n\t"
      "aesdec 0xa0(%6), %%xmm2\n\t"
      "aesdec 0x90(%6), %%xmm2\n\t"
      "aesdec 0x80(%6), %%xmm2\n\t"
      "aesdec 0x70(%6), %%xmm2\n\t"
      "aesdec 0x60(%6), %%xmm2\n\t"
      "aesdec 0x50(%6), %%xmm2\n\t"
      "aesdec 0x40(%6), %%xmm2\n\t"
      "aesdec 0x30(%6), %%xmm2\n\t"
      "aesdec 0x20(%6), %%xmm2\n\t"
      "aesdec 0x10(%6), %%xmm2\n\t"
      "aesdeclast 0x00(%6), %%xmm2\n\t"
      "pxor %%xmm1, %%xmm2\n\t"
      "movdqu (%4), %%xmm1\n\t"
      "movdqu %%xmm2, (%7)\n\t"
#ifdef __LP64__
      "addq $0x10, %4\n\t"
      "addq $0x10, %7\n\t"
#else
      "addl $0x10, %4\n\t"
      "addl $0x10, %7\n\t"
#endif
      "cmpl $0x0f, %3\n\t"
      "jg 1b\n\t"
      "movdqu %%xmm1, (%5)\n\t"
    : "=r" (size), "=r" (p1), "=r" (p2)
    : "0" (size), "1r" (in), "r" (iv), "r" (align16 (ctx)), "2r" (out)
    : "%xmm1", "%xmm2", "memory"
  );
}