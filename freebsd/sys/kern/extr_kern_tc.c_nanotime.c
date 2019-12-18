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
struct timespec {int dummy; } ;
struct bintime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bintime (struct bintime*) ; 
 int /*<<< orphan*/  bintime2timespec (struct bintime*,struct timespec*) ; 

void
nanotime(struct timespec *tsp)
{
	struct bintime bt;

	bintime(&bt);
	bintime2timespec(&bt, tsp);
}