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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct ghes {int dummy; } ;
typedef  int /*<<< orphan*/  DEFINE_RAW_SPINLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_APEI_GHES_SDEI_NORMAL ; 
 int __ghes_sdei_callback (struct ghes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ghes_sdei_normal_callback(u32 event_num, struct pt_regs *regs,
				      void *arg)
{
	static DEFINE_RAW_SPINLOCK(ghes_notify_lock_sdei_normal);
	struct ghes *ghes = arg;
	int err;

	raw_spin_lock(&ghes_notify_lock_sdei_normal);
	err = __ghes_sdei_callback(ghes, FIX_APEI_GHES_SDEI_NORMAL);
	raw_spin_unlock(&ghes_notify_lock_sdei_normal);

	return err;
}