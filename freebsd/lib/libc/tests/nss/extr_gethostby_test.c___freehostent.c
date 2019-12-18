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
struct hostent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  freehostent (struct hostent*) ; 
 scalar_t__ use_ipnode_functions ; 

__attribute__((used)) static void
__freehostent(struct hostent *he)
{

	/* NOTE: checking for he != NULL - just in case */
	if (use_ipnode_functions && he != NULL)
		freehostent(he);
}