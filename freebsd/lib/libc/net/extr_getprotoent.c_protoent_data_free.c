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
struct protoent_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct protoent_data*) ; 
 int /*<<< orphan*/  protoent_data_clear (struct protoent_data*) ; 

__attribute__((used)) static void
protoent_data_free(void *ptr)
{
	struct protoent_data *ped = ptr;

	protoent_data_clear(ped);
	free(ped);
}