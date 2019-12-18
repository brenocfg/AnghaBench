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
 int FORWARD_ADM ; 
 int FORWARD_LOCAL ; 
 int FORWARD_REMOTE ; 
 int FORWARD_USER ; 
 int /*<<< orphan*/  fatal (char*,int,int) ; 

__attribute__((used)) static const char *
fwd_ident(int who, int where)
{
	if (who == FORWARD_ADM) {
		if (where == FORWARD_LOCAL)
			return "admin local";
		else if (where == FORWARD_REMOTE)
			return "admin remote";
	} else if (who == FORWARD_USER) {
		if (where == FORWARD_LOCAL)
			return "user local";
		else if (where == FORWARD_REMOTE)
			return "user remote";
	}
	fatal("Unknown forward permission list %d/%d", who, where);
}