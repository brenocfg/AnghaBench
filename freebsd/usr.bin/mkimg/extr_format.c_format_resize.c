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
typedef  int /*<<< orphan*/  lba_t ;
struct TYPE_2__ {int (* resize ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 TYPE_1__* format ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int
format_resize(lba_t end)
{

	if (format == NULL)
		return (ENOSYS);
	return (format->resize(end));
}