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
struct label_specs {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int STAILQ_EMPTY (int /*<<< orphan*/ *) ; 

int
specs_empty(struct label_specs *specs)
{

	return (STAILQ_EMPTY(&specs->head));
}