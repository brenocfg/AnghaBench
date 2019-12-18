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
typedef  scalar_t__ uint8_t ;
struct t4_sched_queue {int queue; int cl; scalar_t__ port; int /*<<< orphan*/  member_0; } ;
typedef  void* int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_SCHED_QUEUE ; 
 int EINVAL ; 
 long UCHAR_MAX ; 
 int doit (int /*<<< orphan*/ ,struct t4_sched_queue*) ; 
 char* str_to_number (char const*,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
sched_queue(int argc, const char *argv[])
{
	struct t4_sched_queue op = {0};
	char *p;
	long val;

	if (argc != 3) {
		/* need "<port> <queue> <class> */
		warnx("incorrect number of arguments.");
		return (EINVAL);
	}

	p = str_to_number(argv[0], &val, NULL);
	if (*p || val > UCHAR_MAX) {
		warnx("invalid port id \"%s\"", argv[0]);
		return (EINVAL);
	}
	op.port = (uint8_t)val;

	if (!strcmp(argv[1], "all") || !strcmp(argv[1], "*"))
		op.queue = -1;
	else {
		p = str_to_number(argv[1], &val, NULL);
		if (*p || val < -1) {
			warnx("invalid queue \"%s\"", argv[1]);
			return (EINVAL);
		}
		op.queue = (int8_t)val;
	}

	if (!strcmp(argv[2], "unbind") || !strcmp(argv[2], "clear"))
		op.cl = -1;
	else {
		p = str_to_number(argv[2], &val, NULL);
		if (*p || val < -1) {
			warnx("invalid class \"%s\"", argv[2]);
			return (EINVAL);
		}
		op.cl = (int8_t)val;
	}

	return doit(CHELSIO_T4_SCHED_QUEUE, &op);
}