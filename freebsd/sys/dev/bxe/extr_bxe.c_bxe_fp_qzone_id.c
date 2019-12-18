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
typedef  scalar_t__ uint8_t ;
struct bxe_fastpath {scalar_t__ cl_id; int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (int /*<<< orphan*/ ) ; 
 int ETH_MAX_RX_CLIENTS_E1H ; 
 int SC_PORT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t
bxe_fp_qzone_id(struct bxe_fastpath *fp)
{
    if (CHIP_IS_E1x(fp->sc)) {
        return (fp->cl_id + SC_PORT(fp->sc) * ETH_MAX_RX_CLIENTS_E1H);
    } else {
        return (fp->cl_id);
    }
}