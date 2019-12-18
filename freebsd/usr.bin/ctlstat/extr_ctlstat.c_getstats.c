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
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct ctl_io_stats {int alloc_len; int status; int num_items; int fill_len; int flags; TYPE_1__ timestamp; struct ctl_io_stats* stats; } ;
struct ctl_get_io_stats {int alloc_len; int status; int num_items; int fill_len; int flags; TYPE_1__ timestamp; struct ctl_get_io_stats* stats; } ;
typedef  int /*<<< orphan*/  get_stats ;

/* Variables and functions */
 int CTLSTAT_FLAG_PORTS ; 
 int CTLSTAT_FLAG_TIME_VALID ; 
 int /*<<< orphan*/  CTL_GET_LUN_STATS ; 
 int /*<<< orphan*/  CTL_GET_PORT_STATS ; 
#define  CTL_SS_ERROR 130 
#define  CTL_SS_NEED_MORE_SPACE 129 
#define  CTL_SS_OK 128 
 int CTL_STATS_FLAG_TIME_VALID ; 
 int CTL_STAT_NUM_ITEMS ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (struct ctl_io_stats*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ctl_io_stats*) ; 
 struct ctl_io_stats* malloc (int) ; 
 int /*<<< orphan*/  memset (struct ctl_io_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
getstats(int fd, int *alloc_items, int *num_items, struct ctl_io_stats **stats,
	 struct timespec *cur_time, int *flags)
{
	struct ctl_get_io_stats get_stats;
	int more_space_count = 0;

	if (*alloc_items == 0)
		*alloc_items = CTL_STAT_NUM_ITEMS;
retry:
	if (*stats == NULL)
		*stats = malloc(sizeof(**stats) * *alloc_items);

	memset(&get_stats, 0, sizeof(get_stats));
	get_stats.alloc_len = *alloc_items * sizeof(**stats);
	memset(*stats, 0, get_stats.alloc_len);
	get_stats.stats = *stats;

	if (ioctl(fd, (*flags & CTLSTAT_FLAG_PORTS) ? CTL_GET_PORT_STATS :
	    CTL_GET_LUN_STATS, &get_stats) == -1)
		err(1, "CTL_GET_*_STATS ioctl returned error");

	switch (get_stats.status) {
	case CTL_SS_OK:
		break;
	case CTL_SS_ERROR:
		err(1, "CTL_GET_*_STATS ioctl returned CTL_SS_ERROR");
		break;
	case CTL_SS_NEED_MORE_SPACE:
		if (more_space_count >= 2)
			errx(1, "CTL_GET_*_STATS returned NEED_MORE_SPACE again");
		*alloc_items = get_stats.num_items * 5 / 4;
		free(*stats);
		*stats = NULL;
		more_space_count++;
		goto retry;
		break; /* NOTREACHED */
	default:
		errx(1, "CTL_GET_*_STATS ioctl returned unknown status %d",
		     get_stats.status);
		break;
	}

	*num_items = get_stats.fill_len / sizeof(**stats);
	cur_time->tv_sec = get_stats.timestamp.tv_sec;
	cur_time->tv_nsec = get_stats.timestamp.tv_nsec;
	if (get_stats.flags & CTL_STATS_FLAG_TIME_VALID)
		*flags |= CTLSTAT_FLAG_TIME_VALID;
	else
		*flags &= ~CTLSTAT_FLAG_TIME_VALID;

	return (0);
}