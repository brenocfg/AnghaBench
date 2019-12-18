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
 scalar_t__ handle_case_0x7ab (struct torus*,int,int,int) ; 
 scalar_t__ handle_case_0x7ae (struct torus*,int,int,int) ; 
 scalar_t__ handle_case_0x7ba (struct torus*,int,int,int) ; 
 int handle_case_0x7ea (struct torus*,int,int,int) ; 

__attribute__((used)) static
bool handle_case_0x7aa(struct torus *t, int i, int j, int k)
{
	if (handle_case_0x7ab(t, i, j, k))
		return true;

	if (handle_case_0x7ae(t, i, j, k))
		return true;

	if (handle_case_0x7ba(t, i, j, k))
		return true;

	return handle_case_0x7ea(t, i, j, k);
}