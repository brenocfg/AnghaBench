#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* s; } ;
typedef  TYPE_1__ norx32_ctx ;

/* Variables and functions */
 int ROUNDS ; 
 void* rotr32 (int,int) ; 

__attribute__((used)) static void permute(norx32_ctx *ctx)
{
#ifdef CORTEX_M0
  /* Register usage: A-D r2, r3, r4, r5.
   * Temps: r6 */

#define in(xx) "%[" #xx "]"

  /* Load numbered slots of S into r2-r5 */
#define LOAD(u, v, w, x)           \
  "  ldr r2, [%[S], " in(u) "]\n"  \
  "  ldr r3, [%[S], " in(v) "]\n"  \
  "  ldr r4, [%[S], " in(w) "]\n"  \
  "  ldr r5, [%[S], " in(x) "]\n"

  /* Store r2-r5 into numbered slots of S */
#define STORE(u, v, w, x)          \
  "  str r2, [%[S], " in(u) "]\n"  \
  "  str r3, [%[S], " in(v) "]\n"  \
  "  str r4, [%[S], " in(w) "]\n"  \
  "  str r5, [%[S], " in(x) "]\n"

  /* This is H() plus the xor and rotate in one step of G.
   * rx is the register containing x (read/write)
   * ry is the register containing y (read)
   * rw is the register containing d (read/write)
   * rot is the rotation constant r_n */
#define P(rx, ry, rw, rot)      \
  "  mov r6, " #rx "\n"         \
  "  and " #rx ", " #ry "\n"    \
  "  lsl " #rx ", #1\n"         \
  "  eor " #rx ", r6\n"         \
  "  eor " #rx ", " #ry "\n"    \
  "  mov r6, #" #rot "\n"       \
  "  eor " #rw ", " #rx "\n"    \
  "  ror " #rw ", r6\n"

  /* The function G.  s is the state array, a-d are indices
   * into it. */
#define G(s, a, b, c, d)      \
  __asm__ (                   \
            LOAD(A, B, C, D)  \
            P(r2, r3, r5, 8)  \
            P(r4, r5, r3, 11) \
            P(r2, r3, r5, 16) \
            P(r4, r5, r3, 31) \
            STORE(A, B, C, D) \
          :                   \
          : [S] "r" (s),      \
            [A] "i" (a << 2), \
            [B] "i" (b << 2), \
            [C] "i" (c << 2), \
            [D] "i" (d << 2)  \
          : "memory", "cc", "r2", "r3", "r4", "r5", "r6");
#else

  /* This is one quarter of G; the function H plus xor/rotate. */
#define P(u, v, w, rr) \
  (u) = ((u) ^ (v)) ^ (((u) & (v)) << 1); \
  (w) = rotr32((u) ^ (w), rr);

#define G(s, a, b, c, d) \
  P(s[a], s[b], s[d], 8) \
  P(s[c], s[d], s[b], 11) \
  P(s[a], s[b], s[d], 16) \
  P(s[c], s[d], s[b], 31)
#endif

  for (int i = 0; i < ROUNDS; i++)
  {
    /* columns */
    G(ctx->s, 0, 4, 8, 12);
    G(ctx->s, 1, 5, 9, 13);
    G(ctx->s, 2, 6, 10, 14);
    G(ctx->s, 3, 7, 11, 15);

    /* diagonals */
    G(ctx->s, 0, 5, 10, 15);
    G(ctx->s, 1, 6, 11, 12);
    G(ctx->s, 2, 7, 8, 13);
    G(ctx->s, 3, 4, 9, 14);
  }

#undef G
#undef P
}