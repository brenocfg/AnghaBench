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
struct TYPE_2__ {int strdup_strings; } ;
struct shortlog {int /*<<< orphan*/  in2; int /*<<< orphan*/  in1; int /*<<< orphan*/  wrap; TYPE_1__ list; int /*<<< orphan*/  common_repo_prefix; int /*<<< orphan*/  mailmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_INDENT1 ; 
 int /*<<< orphan*/  DEFAULT_INDENT2 ; 
 int /*<<< orphan*/  DEFAULT_WRAPLEN ; 
 int /*<<< orphan*/  memset (struct shortlog*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_mailmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void shortlog_init(struct shortlog *log)
{
	memset(log, 0, sizeof(*log));

	read_mailmap(&log->mailmap, &log->common_repo_prefix);

	log->list.strdup_strings = 1;
	log->wrap = DEFAULT_WRAPLEN;
	log->in1 = DEFAULT_INDENT1;
	log->in2 = DEFAULT_INDENT2;
}