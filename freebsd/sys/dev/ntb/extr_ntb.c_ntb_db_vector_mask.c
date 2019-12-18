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
typedef  int /*<<< orphan*/  uint32_t ;
struct ntb_child {int dboff; int dbmask; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int NTB_DB_VECTOR_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_child* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

uint64_t
ntb_db_vector_mask(device_t ntb, uint32_t vector)
{
	struct ntb_child *nc = device_get_ivars(ntb);

	return ((NTB_DB_VECTOR_MASK(device_get_parent(ntb), vector)
	    >> nc->dboff) & nc->dbmask);
}