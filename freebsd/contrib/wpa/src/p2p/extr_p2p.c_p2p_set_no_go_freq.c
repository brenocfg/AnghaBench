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
struct wpa_freq_range_list {int num; int /*<<< orphan*/  range; } ;
struct wpa_freq_range {int dummy; } ;
struct TYPE_2__ {int num; struct wpa_freq_range* range; } ;
struct p2p_data {TYPE_1__ no_go_freq; } ;

/* Variables and functions */
 struct wpa_freq_range* os_calloc (int,int) ; 
 int /*<<< orphan*/  os_free (struct wpa_freq_range*) ; 
 int /*<<< orphan*/  os_memcpy (struct wpa_freq_range*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p2p_dbg (struct p2p_data*,char*) ; 

int p2p_set_no_go_freq(struct p2p_data *p2p,
		       const struct wpa_freq_range_list *list)
{
	struct wpa_freq_range *tmp;

	if (list == NULL || list->num == 0) {
		os_free(p2p->no_go_freq.range);
		p2p->no_go_freq.range = NULL;
		p2p->no_go_freq.num = 0;
		return 0;
	}

	tmp = os_calloc(list->num, sizeof(struct wpa_freq_range));
	if (tmp == NULL)
		return -1;
	os_memcpy(tmp, list->range, list->num * sizeof(struct wpa_freq_range));
	os_free(p2p->no_go_freq.range);
	p2p->no_go_freq.range = tmp;
	p2p->no_go_freq.num = list->num;
	p2p_dbg(p2p, "Updated no GO chan list");

	return 0;
}