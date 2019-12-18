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
 int /*<<< orphan*/  nmi_mmr_clear ; 
 int /*<<< orphan*/  nmi_mmr_pending ; 
 int /*<<< orphan*/  uv_write_local_mmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void uv_local_mmr_clear_nmi(void)
{
	uv_write_local_mmr(nmi_mmr_clear, nmi_mmr_pending);
}