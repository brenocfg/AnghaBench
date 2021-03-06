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
struct console {int c_flags; } ;

/* Variables and functions */
 int C_PRESENTIN ; 
 int C_PRESENTOUT ; 

__attribute__((used)) static void
c_probe(struct console *cp)
{

	cp->c_flags |= C_PRESENTIN|C_PRESENTOUT;
}