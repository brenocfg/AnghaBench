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
struct p2p_data {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 char const* p2p_state_txt (int /*<<< orphan*/ ) ; 

const char * p2p_get_state_txt(struct p2p_data *p2p)
{
	return p2p_state_txt(p2p->state);
}