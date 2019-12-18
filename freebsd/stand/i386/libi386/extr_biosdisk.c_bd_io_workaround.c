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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  bdinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  BD_RD ; 
 int /*<<< orphan*/  bd_edd_io (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bd_io_workaround(bdinfo_t *bd)
{
	uint8_t buf[8 * 1024];

	bd_edd_io(bd, 0xffffffff, 1, (caddr_t)buf, BD_RD);
}