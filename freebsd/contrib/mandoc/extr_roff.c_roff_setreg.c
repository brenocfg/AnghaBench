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
struct roff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  roff_setregn (struct roff*,char const*,int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
roff_setreg(struct roff *r, const char *name, int val, char sign)
{
	roff_setregn(r, name, strlen(name), val, sign, INT_MIN);
}