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
struct mdchain {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_MINLINE ; 
 int md_get_mem (struct mdchain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
md_get_int64(struct mdchain *mdp, int64_t *x)
{
	return (md_get_mem(mdp, (caddr_t)x, 8, MB_MINLINE));
}