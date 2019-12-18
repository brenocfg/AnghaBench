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
typedef  int u32 ;

/* Variables and functions */
 int rol32 (int,int) ; 

__attribute__((used)) static u32 sm4_key_lin_sub(u32 x)
{
	return x ^ rol32(x, 13) ^ rol32(x, 23);

}