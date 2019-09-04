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
struct grep_source {int /*<<< orphan*/  identifier; int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grep_source_clear_data (struct grep_source*) ; 

void grep_source_clear(struct grep_source *gs)
{
	FREE_AND_NULL(gs->name);
	FREE_AND_NULL(gs->path);
	FREE_AND_NULL(gs->identifier);
	grep_source_clear_data(gs);
}