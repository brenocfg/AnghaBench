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
struct files_state {int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void
files_endstate(void *p)
{

	if (p == NULL)
		return;
	if (((struct files_state *)p)->fp != NULL)
		fclose(((struct files_state *)p)->fp);
	free(p);
}