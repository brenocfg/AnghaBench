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
 int cur_snaplen ; 
 scalar_t__ priv_set_snaplen (int) ; 
 int /*<<< orphan*/  purge_buffer () ; 

int
set_snaplen(int snap)
{
	if (priv_set_snaplen(snap))
		return (1);

	if (cur_snaplen > snap)
		purge_buffer();

	cur_snaplen = snap;

	return (0);
}