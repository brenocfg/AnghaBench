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
struct p2p_data {int min_disc_int; int max_disc_int; int max_disc_tu; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*,int,int,int) ; 

int p2p_set_disc_int(struct p2p_data *p2p, int min_disc_int, int max_disc_int,
		     int max_disc_tu)
{
	if (min_disc_int > max_disc_int || min_disc_int < 0 || max_disc_int < 0)
		return -1;

	p2p->min_disc_int = min_disc_int;
	p2p->max_disc_int = max_disc_int;
	p2p->max_disc_tu = max_disc_tu;
	p2p_dbg(p2p, "Set discoverable interval: min=%d max=%d max_tu=%d",
		min_disc_int, max_disc_int, max_disc_tu);

	return 0;
}