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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SB_MIX_ADDR ; 
 int /*<<< orphan*/  SB_MIX_DATA ; 
 int /*<<< orphan*/  sb_wr (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spltty () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sb_setmixer(struct resource *io, u_int port, u_int value)
{
    	u_long   flags;

    	flags = spltty();
    	sb_wr(io, SB_MIX_ADDR, (u_char) (port & 0xff)); /* Select register */
    	DELAY(10);
    	sb_wr(io, SB_MIX_DATA, (u_char) (value & 0xff));
    	DELAY(10);
    	splx(flags);
}