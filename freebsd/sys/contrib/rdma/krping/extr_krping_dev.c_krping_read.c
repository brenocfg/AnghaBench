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
struct uio {int dummy; } ;
struct stats_list_entry {int /*<<< orphan*/  read_msgs; int /*<<< orphan*/  read_bytes; int /*<<< orphan*/  write_msgs; int /*<<< orphan*/  write_bytes; int /*<<< orphan*/  recv_msgs; int /*<<< orphan*/  recv_bytes; int /*<<< orphan*/  send_msgs; int /*<<< orphan*/  send_bytes; int /*<<< orphan*/  name; struct stats_list_entry* stats; } ;
struct stats_list {int dummy; } ;
struct krping_stats {int /*<<< orphan*/  read_msgs; int /*<<< orphan*/  read_bytes; int /*<<< orphan*/  write_msgs; int /*<<< orphan*/  write_bytes; int /*<<< orphan*/  recv_msgs; int /*<<< orphan*/  recv_bytes; int /*<<< orphan*/  send_msgs; int /*<<< orphan*/  send_bytes; int /*<<< orphan*/  name; struct krping_stats* stats; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ STAILQ_EMPTY (struct stats_list*) ; 
 struct stats_list_entry* STAILQ_FIRST (struct stats_list*) ; 
 int /*<<< orphan*/  STAILQ_INIT (struct stats_list*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct stats_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct stats_list_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krping_copy_stats ; 
 int /*<<< orphan*/  krping_walk_cb_list (int /*<<< orphan*/ ,struct stats_list*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

__attribute__((used)) static int
krping_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	int num = 1;
	struct stats_list list;
	struct stats_list_entry *e;

	STAILQ_INIT(&list);
	krping_walk_cb_list(krping_copy_stats, &list);

	if (STAILQ_EMPTY(&list))
		return (0);

	uprintf("krping: %4s %10s %10s %10s %10s %10s %10s %10s %10s %10s\n",
	    "num", "device", "snd bytes", "snd msgs", "rcv bytes", "rcv msgs",
	    "wr bytes", "wr msgs", "rd bytes", "rd msgs");

	while (!STAILQ_EMPTY(&list)) {
		e = STAILQ_FIRST(&list);
		STAILQ_REMOVE_HEAD(&list, link);
		if (e->stats == NULL)
			uprintf("krping: %d listen\n", num);
		else {
			struct krping_stats *stats = e->stats;

			uprintf("krping: %4d %10s %10llu %10llu %10llu %10llu "
			    "%10llu %10llu %10llu %10llu\n", num, stats->name,
			    stats->send_bytes, stats->send_msgs,
			    stats->recv_bytes, stats->recv_msgs,
			    stats->write_bytes, stats->write_msgs,
			    stats->read_bytes, stats->read_msgs);
			free(stats, M_DEVBUF);
		}
		num++;
		free(e, M_DEVBUF);
	}

	return (0);
}