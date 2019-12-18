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
typedef  union ieee754sp {int dummy; } ieee754sp ;

/* Variables and functions */
 union ieee754sp ieee754sp_div (int /*<<< orphan*/ ,union ieee754sp) ; 
 int /*<<< orphan*/  ieee754sp_one (int /*<<< orphan*/ ) ; 

__attribute__((used)) static union ieee754sp fpemu_sp_recip(union ieee754sp s)
{
	return ieee754sp_div(ieee754sp_one(0), s);
}