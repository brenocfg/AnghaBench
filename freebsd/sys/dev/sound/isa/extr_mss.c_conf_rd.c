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
typedef  int /*<<< orphan*/  u_char ;
struct mss_info {int /*<<< orphan*/  conf_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_rd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char
conf_rd(struct mss_info *mss, u_char reg)
{
	port_wr(mss->conf_base, 0, reg);
    	return port_rd(mss->conf_base, 1);
}