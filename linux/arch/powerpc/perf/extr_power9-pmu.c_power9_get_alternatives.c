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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int isa207_get_alternatives (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power9_event_alternatives ; 

__attribute__((used)) static int power9_get_alternatives(u64 event, unsigned int flags, u64 alt[])
{
	int num_alt = 0;

	num_alt = isa207_get_alternatives(event, alt,
					  ARRAY_SIZE(power9_event_alternatives), flags,
					  power9_event_alternatives);

	return num_alt;
}