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
 int NextConstant4 () ; 
 int pc ; 

__attribute__((used)) static int	Constant4( void ) {
	int		v;

	v = NextConstant4();
	pc += 4;
	return v;
}