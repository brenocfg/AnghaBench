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
struct netent_data {scalar_t__ stayopen; } ;

/* Variables and functions */
 int /*<<< orphan*/  _endnethtent (struct netent_data*) ; 
 int /*<<< orphan*/  free (struct netent_data*) ; 

__attribute__((used)) static void
netent_data_free(void *ptr)
{
	struct netent_data *ned = ptr;

	if (ned == NULL)
		return;
	ned->stayopen = 0;
	_endnethtent(ned);
	free(ned);
}