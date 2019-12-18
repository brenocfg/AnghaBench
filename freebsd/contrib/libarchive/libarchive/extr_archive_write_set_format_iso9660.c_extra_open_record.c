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
struct isoent {int dummy; } ;
struct ctl_extr_rec {unsigned char* bp; int cur_len; int dr_len; int /*<<< orphan*/  limit; int /*<<< orphan*/ * ce_ptr; struct isoent* isoent; scalar_t__ use_extr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_LIMIT ; 

__attribute__((used)) static unsigned char *
extra_open_record(unsigned char *bp, int dr_len, struct isoent *isoent,
    struct ctl_extr_rec *ctl)
{
	ctl->bp = bp;
	if (bp != NULL)
		bp += dr_len;
	ctl->use_extr = 0;
	ctl->isoent = isoent;
	ctl->ce_ptr = NULL;
	ctl->cur_len = ctl->dr_len = dr_len;
	ctl->limit = DR_LIMIT;

	return (bp);
}