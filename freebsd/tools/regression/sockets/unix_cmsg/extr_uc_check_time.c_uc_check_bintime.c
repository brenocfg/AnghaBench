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
 int /*<<< orphan*/  bintime2timespec (struct bintime const*,struct timespec*) ; 
 int uc_check_timespec_real (struct timespec*) ; 

int
uc_check_bintime(const struct bintime *mt)
{
	struct timespec bt;

	bintime2timespec(mt, &bt);
	return (uc_check_timespec_real(&bt));
}