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
struct trailer_item {int dummy; } ;
struct arg_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ same_token (struct trailer_item*,struct arg_item*) ; 
 scalar_t__ same_value (struct trailer_item*,struct arg_item*) ; 

__attribute__((used)) static int same_trailer(struct trailer_item *a, struct arg_item *b)
{
	return same_token(a, b) && same_value(a, b);
}