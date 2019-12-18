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
struct intr_map_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INTRNG ; 
 int /*<<< orphan*/  free (struct intr_map_data*,int /*<<< orphan*/ ) ; 

void intr_free_intr_map_data(struct intr_map_data *data)
{

	free(data, M_INTRNG);
}