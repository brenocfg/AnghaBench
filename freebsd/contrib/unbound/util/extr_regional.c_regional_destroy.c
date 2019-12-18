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
struct regional {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct regional*) ; 
 int /*<<< orphan*/  regional_free_all (struct regional*) ; 

void 
regional_destroy(struct regional *r)
{
	if(!r) return;
	regional_free_all(r);
	free(r);
}