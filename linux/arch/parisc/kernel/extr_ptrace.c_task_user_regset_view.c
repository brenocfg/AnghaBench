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
struct user_regset_view {int dummy; } ;
struct user_regs_struct {int dummy; } ;
struct user_fp_struct {int dummy; } ;
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ELF_NFPREG ; 
 int ELF_NGREG ; 
 scalar_t__ is_compat_task () ; 
 struct user_regset_view const user_parisc_compat_view ; 
 struct user_regset_view const user_parisc_native_view ; 

const struct user_regset_view *task_user_regset_view(struct task_struct *task)
{
	BUILD_BUG_ON(sizeof(struct user_regs_struct)/sizeof(long) != ELF_NGREG);
	BUILD_BUG_ON(sizeof(struct user_fp_struct)/sizeof(__u64) != ELF_NFPREG);
#ifdef CONFIG_64BIT
	if (is_compat_task())
		return &user_parisc_compat_view;
#endif
	return &user_parisc_native_view;
}