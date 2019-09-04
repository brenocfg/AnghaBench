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
struct packed_git {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_pack_fd (struct packed_git*) ; 
 int /*<<< orphan*/  close_pack_index (struct packed_git*) ; 
 int /*<<< orphan*/  close_pack_windows (struct packed_git*) ; 

void close_pack(struct packed_git *p)
{
	close_pack_windows(p);
	close_pack_fd(p);
	close_pack_index(p);
}