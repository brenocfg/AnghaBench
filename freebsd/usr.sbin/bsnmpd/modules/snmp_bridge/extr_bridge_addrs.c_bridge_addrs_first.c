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
struct tp_entry {int dummy; } ;

/* Variables and functions */
 struct tp_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tp_entries ; 

__attribute__((used)) static struct tp_entry *
bridge_addrs_first(void)
{
	return (TAILQ_FIRST(&tp_entries));
}