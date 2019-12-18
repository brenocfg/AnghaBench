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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */

__attribute__((used)) static bool any_left_hand_identifier(git_object *object, git_reference *reference, size_t identifier_len)
{
	if (object != NULL)
		return true;

	if (reference != NULL)
		return true;

	if (identifier_len > 0)
		return true;

	return false;
}