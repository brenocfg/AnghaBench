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
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ ocb ;
typedef  int /*<<< orphan*/  cf_gf128 ;

/* Variables and functions */
 size_t MAX_L ; 
 int /*<<< orphan*/  cf_gf128_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_gf128_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocb_add_Ln(ocb *o, uint32_t n, cf_gf128 out)
{
  /* Do we have a precomputed L term? */
  if (n < MAX_L)
  {
    cf_gf128_add(o->L[n], out, out);
    return;
  }

  /* Compute more terms of L. */
  cf_gf128 accum;
  memcpy(accum, o->L[MAX_L - 1], sizeof accum);

  for (uint32_t i = MAX_L - 1; i < n; i++)
  {
    cf_gf128 next;
    cf_gf128_double(accum, next);
    memcpy(accum, next, sizeof accum);
  }

  cf_gf128_add(accum, out, out);
}