#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* message; } ;
typedef  TYPE_1__ git_tag ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

const char *git_tag_message(const git_tag *t)
{
	assert(t);
	return t->message;
}