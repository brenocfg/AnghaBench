#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ ifi_ibytes; } ;
struct TYPE_4__ {TYPE_1__ ifmd_data; } ;
struct if_stat {int match; int display; TYPE_2__ if_mib; scalar_t__ if_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFSTAT_ERR (int,char*) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct if_stat*,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  curlist ; 
 int /*<<< orphan*/  getifmibdata (scalar_t__,TYPE_2__*) ; 
 scalar_t__ getifnum () ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  right_align_string (struct if_stat*) ; 
 int /*<<< orphan*/  sort_interface_list () ; 

int
initifstat(void)
{
	struct   if_stat *p = NULL;
	u_int	 n = 0, i = 0;

	n = getifnum();
	if (n <= 0)
		return (-1);

	SLIST_INIT(&curlist);

	for (i = 0; i < n; i++) {
		p = (struct if_stat *)calloc(1, sizeof(struct if_stat));
		if (p == NULL)
			IFSTAT_ERR(1, "out of memory");
		SLIST_INSERT_HEAD(&curlist, p, link);
		p->if_row = i+1;
		getifmibdata(p->if_row, &p->if_mib);
		right_align_string(p);
		p->match = 1;

		/*
		 * Initially, we only display interfaces that have
		 * received some traffic.
		 */
		if (p->if_mib.ifmd_data.ifi_ibytes != 0)
			p->display = 1;
	}

	sort_interface_list();

	return (1);
}