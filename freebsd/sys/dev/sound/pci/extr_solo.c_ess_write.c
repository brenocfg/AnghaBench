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
struct ess_info {int dummy; } ;

/* Variables and functions */
 int ess_cmd1 (struct ess_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ess_write(struct ess_info *sc, u_char reg, int val)
{
    	return ess_cmd1(sc, reg, val);
}