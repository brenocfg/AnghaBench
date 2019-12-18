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
typedef  int u_char ;
struct sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 
 int sb_dspwr (struct sb_info*,int) ; 

__attribute__((used)) static int
sb_cmd(struct sb_info *sb, u_char val)
{
#if 0
	printf("sb_cmd: %x\n", val);
#endif
    	return sb_dspwr(sb, val);
}