#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ SW_REV ;

/* Variables and functions */
 int /*<<< orphan*/  get_lsb_uint16 (unsigned char**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

void
get_mbg_sw_rev(
	unsigned char **bufpp,
	SW_REV *sw_revp
	)
{
  sw_revp->code = get_lsb_uint16(bufpp);
  memcpy(sw_revp->name, *bufpp, sizeof(sw_revp->name));
  *bufpp += sizeof(sw_revp->name);
}