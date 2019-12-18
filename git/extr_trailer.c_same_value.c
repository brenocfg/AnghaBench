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
struct trailer_item {int /*<<< orphan*/  value; } ;
struct arg_item {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int same_value(struct trailer_item *a, struct arg_item *b)
{
	return !strcasecmp(a->value, b->value);
}