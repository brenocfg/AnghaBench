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
typedef  int /*<<< orphan*/  teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_funcs_bell (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
teken_subr_bell(const teken_t *t)
{

	teken_funcs_bell(t);
}