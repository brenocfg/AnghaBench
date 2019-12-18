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

/* Variables and functions */

__attribute__((used)) static int
fatend(u_int sz, u_int c)
{
    return (c > (sz == 12 ? 0xff7U : sz == 16 ? 0xfff7U : 0xffffff7));
}