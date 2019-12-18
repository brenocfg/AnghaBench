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
struct wpa_bss_anqp {int users; int /*<<< orphan*/  anqp_elems; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 struct wpa_bss_anqp* os_zalloc (int) ; 

struct wpa_bss_anqp * wpa_bss_anqp_alloc(void)
{
	struct wpa_bss_anqp *anqp;
	anqp = os_zalloc(sizeof(*anqp));
	if (anqp == NULL)
		return NULL;
#ifdef CONFIG_INTERWORKING
	dl_list_init(&anqp->anqp_elems);
#endif /* CONFIG_INTERWORKING */
	anqp->users = 1;
	return anqp;
}