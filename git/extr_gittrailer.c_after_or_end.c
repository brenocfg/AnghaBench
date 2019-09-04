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
typedef  enum trailer_where { ____Placeholder_trailer_where } trailer_where ;

/* Variables and functions */
 int WHERE_AFTER ; 
 int WHERE_END ; 

__attribute__((used)) static int after_or_end(enum trailer_where where)
{
	return (where == WHERE_AFTER) || (where == WHERE_END);
}