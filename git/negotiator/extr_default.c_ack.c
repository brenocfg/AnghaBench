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
 int COMMON ; 
 int /*<<< orphan*/  mark_common (int /*<<< orphan*/ ,struct commit*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ack(struct fetch_negotiator *n, struct commit *c)
{
	int known_to_be_common = !!(c->object.flags & COMMON);
	mark_common(n->data, c, 0, 1);
	return known_to_be_common;
}