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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
#define  O_TAGS 128 
 int ex_tagf_alloc (int /*<<< orphan*/ *,char*) ; 

int
ex_optchange(SCR *sp, int offset, char *str, u_long *valp)
{
	switch (offset) {
	case O_TAGS:
		return (ex_tagf_alloc(sp, str));
	}
	return (0);
}