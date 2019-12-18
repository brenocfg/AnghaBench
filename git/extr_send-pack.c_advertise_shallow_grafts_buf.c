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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  advertise_shallow_grafts_cb ; 
 int /*<<< orphan*/  for_each_commit_graft (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  is_repository_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void advertise_shallow_grafts_buf(struct strbuf *sb)
{
	if (!is_repository_shallow(the_repository))
		return;
	for_each_commit_graft(advertise_shallow_grafts_cb, sb);
}