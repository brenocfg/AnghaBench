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
typedef  int uint64_t ;
struct cvmx_power_throttle_rfield_t {int pos; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int CVMX_PTH_GET_MASK (int /*<<< orphan*/ ,int) ; 
 int CVMX_PTH_INDEX_MAX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cvmx_power_throttle_rfield_t* cvmx_power_throttle_rfield ; 

__attribute__((used)) static int cvmx_power_throttle_set_field(int i, uint64_t r, uint64_t v)
{
    if (OCTEON_IS_MODEL(OCTEON_CN6XXX))
    {
        uint64_t m;
        struct cvmx_power_throttle_rfield_t *p;

        assert(i < CVMX_PTH_INDEX_MAX);

        p = &cvmx_power_throttle_rfield[i];
        m = CVMX_PTH_GET_MASK(p->len, p->pos);

        return((~m & r) | ((v << p->pos) & m));
    }
    return 0;
}