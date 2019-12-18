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
typedef  int /*<<< orphan*/  au_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_SEMSYS ; 
 int /*<<< orphan*/ * aue_semsys ; 
 int aue_semsys_count ; 

au_event_t
audit_semsys_to_event(int which)
{

	if ((which >= 0) && (which < aue_semsys_count))
		return (aue_semsys[which]);

	/* Audit a bad command. */
	return (AUE_SEMSYS);
}