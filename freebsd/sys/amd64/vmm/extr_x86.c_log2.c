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
 int fls (int) ; 
 int powerof2 (int) ; 

__attribute__((used)) static __inline int
log2(u_int x)
{

	return (fls(x << (1 - powerof2(x))) - 1);
}