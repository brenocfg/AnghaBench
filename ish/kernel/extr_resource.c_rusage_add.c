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
struct rusage_ {int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;

/* Variables and functions */
 int /*<<< orphan*/  timeval_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rusage_add(struct rusage_ *dst, struct rusage_ *src) {
    timeval_add(&dst->utime, &src->utime);
    timeval_add(&dst->stime, &src->stime);
}