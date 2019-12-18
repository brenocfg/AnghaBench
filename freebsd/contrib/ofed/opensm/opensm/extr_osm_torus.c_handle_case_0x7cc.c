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
struct torus {int dummy; } ;

/* Variables and functions */
 scalar_t__ handle_case_0x7cd (struct torus*,int,int,int) ; 
 scalar_t__ handle_case_0x7ce (struct torus*,int,int,int) ; 
 scalar_t__ handle_case_0x7dc (struct torus*,int,int,int) ; 
 int handle_case_0x7ec (struct torus*,int,int,int) ; 

__attribute__((used)) static
bool handle_case_0x7cc(struct torus *t, int i, int j, int k)
{
	if (handle_case_0x7cd(t, i, j, k))
		return true;

	if (handle_case_0x7ce(t, i, j, k))
		return true;

	if (handle_case_0x7dc(t, i, j, k))
		return true;

	return handle_case_0x7ec(t, i, j, k);
}