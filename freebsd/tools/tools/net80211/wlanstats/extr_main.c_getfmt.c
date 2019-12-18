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
struct TYPE_3__ {char const* fmt; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int nitems (TYPE_1__*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* tags ; 

__attribute__((used)) static const char *
getfmt(const char *tag)
{
	int i;
	for (i = 0; i < nitems(tags); i++)
		if (strcasecmp(tags[i].tag, tag) == 0)
			return tags[i].fmt;
	return tag;
}