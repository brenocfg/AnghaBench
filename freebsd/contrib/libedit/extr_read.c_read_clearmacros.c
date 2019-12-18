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
struct macros {scalar_t__ level; scalar_t__ offset; int /*<<< orphan*/ * macro; } ;

/* Variables and functions */
 int /*<<< orphan*/  el_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_clearmacros(struct macros *ma)
{
	while (ma->level >= 0)
		el_free(ma->macro[ma->level--]);
	ma->offset = 0;
}