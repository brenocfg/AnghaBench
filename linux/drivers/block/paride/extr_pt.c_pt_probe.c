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
struct pt_unit {int drive; } ;

/* Variables and functions */
 int pt_identify (struct pt_unit*) ; 
 int /*<<< orphan*/  pt_reset (struct pt_unit*) ; 

__attribute__((used)) static int pt_probe(struct pt_unit *tape)
{
	if (tape->drive == -1) {
		for (tape->drive = 0; tape->drive <= 1; tape->drive++)
			if (!pt_reset(tape))
				return pt_identify(tape);
	} else {
		if (!pt_reset(tape))
			return pt_identify(tape);
	}
	return -1;
}