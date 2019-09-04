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
struct object_id {int dummy; } ;
struct fetch_negotiator {int /*<<< orphan*/  data; int /*<<< orphan*/ * add_tip; int /*<<< orphan*/ * known_common; } ;

/* Variables and functions */
 struct object_id const* get_rev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct object_id *next(struct fetch_negotiator *n)
{
	n->known_common = NULL;
	n->add_tip = NULL;
	return get_rev(n->data);
}