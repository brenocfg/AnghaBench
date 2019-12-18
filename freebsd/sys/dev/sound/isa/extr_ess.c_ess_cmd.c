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
struct ess_info {int dummy; } ;

/* Variables and functions */
 int ess_dspwr (struct ess_info*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
ess_cmd(struct ess_info *sc, u_char val)
{
#if 0
	printf("ess_cmd: %x\n", val);
#endif
    	return ess_dspwr(sc, val);
}