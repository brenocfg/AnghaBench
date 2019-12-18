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
struct jailparam {int jp_flags; int /*<<< orphan*/  jp_value; int /*<<< orphan*/  jp_name; } ;

/* Variables and functions */
 int JP_RAWVALUE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
jailparam_free(struct jailparam *jp, unsigned njp)
{
	unsigned j;

	for (j = 0; j < njp; j++) {
		free(jp[j].jp_name);
		if (!(jp[j].jp_flags & JP_RAWVALUE))
			free(jp[j].jp_value);
	}
}