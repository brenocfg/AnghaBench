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

/* Variables and functions */
 int ERANGE ; 
 double HUGE_VAL ; 
 double HUGE_VALF ; 
 double HUGE_VALL ; 

__attribute__((used)) static inline bool
huge_plus(double d, int err1)
{

	if (err1 == ERANGE)
		if (d == HUGE_VAL || d == HUGE_VALF || d == HUGE_VALL)
			return (+1);

	return (0);
}