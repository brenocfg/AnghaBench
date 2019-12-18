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
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_part_null_scheme ; 
 int /*<<< orphan*/  g_part_schemes ; 
 int /*<<< orphan*/  scheme_list ; 

__attribute__((used)) static void
g_part_fini(struct g_class *mp)
{

	TAILQ_REMOVE(&g_part_schemes, &g_part_null_scheme, scheme_list);
}