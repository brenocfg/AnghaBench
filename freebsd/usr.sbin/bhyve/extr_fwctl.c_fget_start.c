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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int E2BIG ; 
 scalar_t__ FGET_STRSZ ; 
 scalar_t__ fget_cnt ; 

__attribute__((used)) static int
fget_start(uint32_t len)
{

	if (len > FGET_STRSZ)
		return(E2BIG);

	fget_cnt = 0;

	return (0);
}