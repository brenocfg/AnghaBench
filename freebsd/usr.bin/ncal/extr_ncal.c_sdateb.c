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
struct date {int dummy; } ;

/* Variables and functions */
 struct date* gdate (int,struct date*) ; 
 struct date* jdate (int,struct date*) ; 
 int nswitchb ; 

__attribute__((used)) static struct date *
sdateb(int nd, struct date *d)
{

	if (nswitchb < nd)
		return (gdate(nd, d));
	else
		return (jdate(nd, d));
}