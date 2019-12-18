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
typedef  int u_int32_t ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int cs4281_rd (struct sc_info*,int) ; 

__attribute__((used)) static int
cs4281_waitset(struct sc_info *sc, int regno, u_int32_t mask, int tries)
{
    u_int32_t v;

    while (tries > 0) {
	DELAY(100);
	v = cs4281_rd(sc, regno);
	if ((v & mask) == mask) break;
	tries --;
    }
    return tries;
}