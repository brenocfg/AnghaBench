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
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bootcode ; 
 TYPE_1__* scheme ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
scheme_write(lba_t end)
{

	return ((scheme == NULL) ? 0 : scheme->write(end, bootcode));
}