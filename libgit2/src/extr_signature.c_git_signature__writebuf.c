#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int offset; char sign; scalar_t__ time; } ;
struct TYPE_5__ {TYPE_1__ when; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_signature ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,char,int,int) ; 

void git_signature__writebuf(git_buf *buf, const char *header, const git_signature *sig)
{
	int offset, hours, mins;
	char sign;

	assert(buf && sig);

	offset = sig->when.offset;
	sign = (sig->when.offset < 0 || sig->when.sign == '-') ? '-' : '+';

	if (offset < 0)
		offset = -offset;

	hours = offset / 60;
	mins = offset % 60;

	git_buf_printf(buf, "%s%s <%s> %u %c%02d%02d\n",
			header ? header : "", sig->name, sig->email,
			(unsigned)sig->when.time, sign, hours, mins);
}