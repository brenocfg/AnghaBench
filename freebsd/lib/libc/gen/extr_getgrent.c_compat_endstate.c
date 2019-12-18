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
struct compat_state {void* name; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void
compat_endstate(void *p)
{
	struct compat_state *st;

	if (p == NULL)
		return;
	st = (struct compat_state *)p;
	free(st->name);
	if (st->fp != NULL)
		fclose(st->fp);
	free(p);
}