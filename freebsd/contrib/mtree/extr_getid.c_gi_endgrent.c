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

/* Variables and functions */
 scalar_t__ _gr_filesdone ; 
 int /*<<< orphan*/ * _gr_fp ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gi_endgrent(void)
{

	_gr_filesdone = 0;
	if (_gr_fp) {
		(void)fclose(_gr_fp);
		_gr_fp = NULL;
	}
}