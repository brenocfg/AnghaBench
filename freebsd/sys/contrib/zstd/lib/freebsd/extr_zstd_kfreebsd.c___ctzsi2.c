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
typedef  int /*<<< orphan*/  x ;

/* Variables and functions */
 int NBBY ; 
 int ffs (int) ; 

int
__ctzsi2(int x)
{
       if (x == 0)
               return (sizeof(x) * NBBY);
       return (ffs(x) - 1);
}