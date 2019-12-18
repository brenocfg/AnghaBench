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
struct utmpx {int dummy; } ;
struct futx {int dummy; } ;

/* Variables and functions */
 struct utmpx* futx_to_utx (struct futx*) ; 
 scalar_t__ getfutxent (struct futx*) ; 

struct utmpx *
getutxent(void)
{
	struct futx fu;

	if (getfutxent(&fu) != 0)
		return (NULL);
	return (futx_to_utx(&fu));
}