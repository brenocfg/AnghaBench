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
typedef  int uint64_t ;
struct ntb_child {int dboff; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void NTB_DB_SET_MASK (int /*<<< orphan*/ ,int) ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

void
ntb_db_set_mask(device_t ntb, uint64_t bits)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	return (NTB_DB_SET_MASK(device_get_parent(ntb), bits << nc->dboff));
}