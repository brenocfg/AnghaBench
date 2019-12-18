#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_word ;
struct TYPE_13__ {scalar_t__ used; scalar_t__* dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  scalar_t__ mp_digit ;

/* Variables and functions */
 int CHAR_BIT ; 
 int DIGIT_BIT ; 
 int MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ MP_MASK ; 
 int MP_OKAY ; 
 scalar_t__ MP_WARRAY ; 
 int fast_s_mp_mul_high_digs (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mp_clamp (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_exch (TYPE_1__*,TYPE_1__*) ; 
 int mp_init_size (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int s_mp_mul_high_digs (mp_int * a, mp_int * b, mp_int * c, int digs)
{
  mp_int  t;
  int     res, pa, pb, ix, iy;
  mp_digit u;
  mp_word r;
  mp_digit tmpx, *tmpt, *tmpy;

  /* can we use the fast multiplier? */
#ifdef BN_FAST_S_MP_MUL_HIGH_DIGS_C
  if (((a->used + b->used + 1) < MP_WARRAY)
      && MIN (a->used, b->used) < (1 << ((CHAR_BIT * sizeof (mp_word)) - (2 * DIGIT_BIT)))) {
    return fast_s_mp_mul_high_digs (a, b, c, digs);
  }
#endif

  if ((res = mp_init_size (&t, a->used + b->used + 1)) != MP_OKAY) {
    return res;
  }
  t.used = a->used + b->used + 1;

  pa = a->used;
  pb = b->used;
  for (ix = 0; ix < pa; ix++) {
    /* clear the carry */
    u = 0;

    /* left hand side of A[ix] * B[iy] */
    tmpx = a->dp[ix];

    /* alias to the address of where the digits will be stored */
    tmpt = &(t.dp[digs]);

    /* alias for where to read the right hand side from */
    tmpy = b->dp + (digs - ix);

    for (iy = digs - ix; iy < pb; iy++) {
      /* calculate the double precision result */
      r       = ((mp_word)*tmpt) +
                ((mp_word)tmpx) * ((mp_word)*tmpy++) +
                ((mp_word) u);

      /* get the lower part */
      *tmpt++ = (mp_digit) (r & ((mp_word) MP_MASK));

      /* carry the carry */
      u       = (mp_digit) (r >> ((mp_word) DIGIT_BIT));
    }
    *tmpt = u;
  }
  mp_clamp (&t);
  mp_exch (&t, c);
  mp_clear (&t);
  return MP_OKAY;
}