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
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  discard_my_cleanups (int /*<<< orphan*/ *,struct cleanup*) ; 
 int /*<<< orphan*/  final_cleanup_chain ; 

void
discard_final_cleanups (struct cleanup *old_chain)
{
  discard_my_cleanups (&final_cleanup_chain, old_chain);
}