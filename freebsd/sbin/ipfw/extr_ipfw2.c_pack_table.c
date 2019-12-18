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
typedef  int /*<<< orphan*/  uint16_t ;
struct tidx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TLV_TBL_NAME ; 
 int /*<<< orphan*/  pack_object (struct tidx*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ table_check_name (char*) ; 

__attribute__((used)) static uint16_t
pack_table(struct tidx *tstate, char *name)
{

	if (table_check_name(name) != 0)
		return (0);

	return (pack_object(tstate, name, IPFW_TLV_TBL_NAME));
}