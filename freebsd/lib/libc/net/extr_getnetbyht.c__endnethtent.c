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
struct netent_data {scalar_t__ stayopen; int /*<<< orphan*/ * netf; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 

void
_endnethtent(struct netent_data *ned)
{

	if (ned->netf) {
		fclose(ned->netf);
		ned->netf = NULL;
	}
	ned->stayopen = 0;
}