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
struct stats_list_entry {struct krping_stats* stats; } ;
struct stats_list {int dummy; } ;
struct krping_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct stats_list*,struct stats_list_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct stats_list_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
krping_copy_stats(struct krping_stats *stats, void *arg)
{
	struct stats_list_entry *s;
	struct stats_list *list = arg;

	s = malloc(sizeof(*s), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (s == NULL)
		return;
	if (stats != NULL) {
		s->stats = malloc(sizeof(*stats), M_DEVBUF, M_NOWAIT | M_ZERO);
		if (s->stats == NULL) {
			free(s, M_DEVBUF);
			return;
		}
		*s->stats = *stats;
	}
	STAILQ_INSERT_TAIL(list, s, link);
}