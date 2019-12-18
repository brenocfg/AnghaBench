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
typedef  int /*<<< orphan*/  uint8_t ;
struct mdchain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB_MINLINE ; 
 int md_get_mem (struct mdchain*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
md_get_uint8(struct mdchain *mdp, uint8_t *x)
{
	return (md_get_mem(mdp, x, 1, MB_MINLINE));
}