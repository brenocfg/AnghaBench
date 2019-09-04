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

/* Variables and functions */
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  sigchain_pop (int) ; 
 int /*<<< orphan*/  the_tmp_objdir ; 
 int /*<<< orphan*/  tmp_objdir_destroy_1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void remove_tmp_objdir_on_signal(int signo)
{
	tmp_objdir_destroy_1(the_tmp_objdir, 1);
	sigchain_pop(signo);
	raise(signo);
}