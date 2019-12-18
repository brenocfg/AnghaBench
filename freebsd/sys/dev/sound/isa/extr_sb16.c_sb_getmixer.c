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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SB_MIX_ADDR ; 
 int /*<<< orphan*/  SB_MIX_DATA ; 
 int /*<<< orphan*/  sb_lockassert (struct sb_info*) ; 
 int sb_rd (struct sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_wr (struct sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sb_getmixer(struct sb_info *sb, u_int port)
{
    	int val;

    	sb_lockassert(sb);
    	sb_wr(sb, SB_MIX_ADDR, (u_char) (port & 0xff)); /* Select register */
    	DELAY(10);
    	val = sb_rd(sb, SB_MIX_DATA);
    	DELAY(10);

    	return val;
}