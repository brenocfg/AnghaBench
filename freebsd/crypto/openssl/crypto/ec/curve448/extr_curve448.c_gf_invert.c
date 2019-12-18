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
typedef  int /*<<< orphan*/  mask_t ;
typedef  int /*<<< orphan*/  const gf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gf_copy (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gf_isr (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gf_mul (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gf_sqr (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void gf_invert(gf y, const gf x, int assert_nonzero)
{
    mask_t ret;
    gf t1, t2;

    gf_sqr(t1, x);              /* o^2 */
    ret = gf_isr(t2, t1);       /* +-1/sqrt(o^2) = +-1/o */
    (void)ret;
    if (assert_nonzero)
        assert(ret);
    gf_sqr(t1, t2);
    gf_mul(t2, t1, x);          /* not direct to y in case of alias. */
    gf_copy(y, t2);
}