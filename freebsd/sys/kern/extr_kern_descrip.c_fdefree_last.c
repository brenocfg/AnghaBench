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
struct filedescent {int /*<<< orphan*/  fde_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  filecaps_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
fdefree_last(struct filedescent *fde)
{

	filecaps_free(&fde->fde_caps);
}