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
struct port_info {struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_LOCK (struct adapter*) ; 
 int /*<<< orphan*/  ADAPTER_LOCK_ASSERT_NOTOWNED (struct adapter*) ; 
 int /*<<< orphan*/  cxgb_init_locked (struct port_info*) ; 

__attribute__((used)) static void
cxgb_init(void *arg)
{
	struct port_info *p = arg;
	struct adapter *sc = p->adapter;

	ADAPTER_LOCK(sc);
	cxgb_init_locked(p); /* releases adapter lock */
	ADAPTER_LOCK_ASSERT_NOTOWNED(sc);
}