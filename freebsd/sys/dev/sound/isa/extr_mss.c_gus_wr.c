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
 int /*<<< orphan*/  port_wr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gus_wr(struct mss_info *mss, u_char reg, u_char value)
{
    	port_wr(mss->conf_base, 3, reg);
    	port_wr(mss->conf_base, 5, value);
}