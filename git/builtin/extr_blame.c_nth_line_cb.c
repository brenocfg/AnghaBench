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
struct blame_scoreboard {int dummy; } ;

/* Variables and functions */
 char const* blame_nth_line (struct blame_scoreboard*,long) ; 

__attribute__((used)) static const char *nth_line_cb(void *data, long lno)
{
	return blame_nth_line((struct blame_scoreboard *)data, lno);
}