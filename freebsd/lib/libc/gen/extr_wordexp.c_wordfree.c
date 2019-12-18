#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ we_wordc; scalar_t__ we_nbytes; int /*<<< orphan*/ * we_strings; int /*<<< orphan*/ * we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
wordfree(wordexp_t *we)
{

	if (we == NULL)
		return;
	free(we->we_wordv);
	free(we->we_strings);
	we->we_wordv = NULL;
	we->we_strings = NULL;
	we->we_nbytes = 0;
	we->we_wordc = 0;
}