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
struct macros {int level; scalar_t__ offset; int /*<<< orphan*/ * macro; } ;

/* Variables and functions */
 int /*<<< orphan*/  el_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
read_pop(struct macros *ma)
{
	int i;

	el_free(ma->macro[0]);
	for (i = 0; i < ma->level; i++)
		ma->macro[i] = ma->macro[i + 1];
	ma->level--;
	ma->offset = 0;
}