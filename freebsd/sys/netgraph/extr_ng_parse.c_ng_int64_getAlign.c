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
struct ng_parse_type {int dummy; } ;

/* Variables and functions */
 int INT64_ALIGNMENT ; 

__attribute__((used)) static int
ng_int64_getAlign(const struct ng_parse_type *type)
{
	return INT64_ALIGNMENT;
}