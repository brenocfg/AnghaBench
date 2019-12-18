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
struct timeval {int dummy; } ;
struct bintime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bintime2timeval (struct bintime*,struct timeval*) ; 
 int /*<<< orphan*/  binuptime (struct bintime*) ; 

void
microuptime(struct timeval *tvp)
{
	struct bintime bt;

	binuptime(&bt);
	bintime2timeval(&bt, tvp);
}