#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct message {TYPE_1__ ts; int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show(const char *prefix, const struct message *msg)
{
	printf("%10.10s: %zu [%jd.%ld]\n", prefix, msg->seq, (intmax_t)
	    msg->ts.tv_sec, msg->ts.tv_nsec);
}