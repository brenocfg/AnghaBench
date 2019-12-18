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
typedef  int /*<<< orphan*/  file_pair ;

/* Variables and functions */
 int io_open_dest_real (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signals_block () ; 
 int /*<<< orphan*/  signals_unblock () ; 

extern bool
io_open_dest(file_pair *pair)
{
	signals_block();
	const bool ret = io_open_dest_real(pair);
	signals_unblock();
	return ret;
}