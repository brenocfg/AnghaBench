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
struct exportlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  out_of_mem () ; 

__attribute__((used)) static struct exportlist *
get_exp(void)
{
	struct exportlist *ep;

	ep = (struct exportlist *)calloc(1, sizeof (struct exportlist));
	if (ep == (struct exportlist *)NULL)
		out_of_mem();
	return (ep);
}