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
struct gre_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GRE ; 
 int /*<<< orphan*/  free (struct gre_list*,int /*<<< orphan*/ ) ; 

void
gre_hashdestroy(struct gre_list *hash)
{

	free(hash, M_GRE);
}