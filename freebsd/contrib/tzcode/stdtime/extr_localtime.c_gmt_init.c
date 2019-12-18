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
struct state {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  gmtload (struct state*) ; 
 struct state* gmtptr ; 

__attribute__((used)) static void
gmt_init(void)
{

#ifdef ALL_STATE
	gmtptr = (struct state *) calloc(1, sizeof *gmtptr);
	if (gmtptr != NULL)
#endif /* defined ALL_STATE */
		gmtload(gmtptr);
}