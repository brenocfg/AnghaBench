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
struct g_gsched {int /*<<< orphan*/  gs_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
g_gsched_ref(struct g_gsched *gsp)
{

	atomic_add_int(&gsp->gs_refs, 1);
}