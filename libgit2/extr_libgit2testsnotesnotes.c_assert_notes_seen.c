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
struct note_create_payload {scalar_t__ seen; int /*<<< orphan*/ * note_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 

void assert_notes_seen(struct note_create_payload payload[], size_t n)
{
	size_t seen = 0, i;

	for (i = 0; payload[i].note_oid != NULL; i++) {
		if (payload[i].seen)
			seen++;
	}

	cl_assert_equal_i(seen, n);
}