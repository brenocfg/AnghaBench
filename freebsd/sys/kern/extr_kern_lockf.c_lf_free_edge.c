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
struct lockf_edge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_LOCKF ; 
 int /*<<< orphan*/  free (struct lockf_edge*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lf_free_edge(struct lockf_edge *e)
{

	free(e, M_LOCKF);
}