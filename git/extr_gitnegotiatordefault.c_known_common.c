#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fetch_negotiator {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int COMMON_REF ; 
 int SEEN ; 
 int /*<<< orphan*/  mark_common (int /*<<< orphan*/ ,struct commit*,int,int) ; 
 int /*<<< orphan*/  rev_list_push (int /*<<< orphan*/ ,struct commit*,int) ; 

__attribute__((used)) static void known_common(struct fetch_negotiator *n, struct commit *c)
{
	if (!(c->object.flags & SEEN)) {
		rev_list_push(n->data, c, COMMON_REF | SEEN);
		mark_common(n->data, c, 1, 1);
	}
}