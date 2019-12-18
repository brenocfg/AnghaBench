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
typedef  int /*<<< orphan*/  drv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void cx_initialize (void *softc)
{
	drv_t *d = softc;

	CX_DEBUG (d, ("cx_initialize\n"));
}