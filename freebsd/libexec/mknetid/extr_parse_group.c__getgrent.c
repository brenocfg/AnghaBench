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
struct group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _gr_fp ; 
 struct group _gr_group ; 
 int /*<<< orphan*/  grscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_gr () ; 

struct group *
_getgrent(void)
{
	if (!_gr_fp && !start_gr()) {
		return NULL;
	}


	if (!grscan(0, 0))
		return(NULL);
	return(&_gr_group);
}