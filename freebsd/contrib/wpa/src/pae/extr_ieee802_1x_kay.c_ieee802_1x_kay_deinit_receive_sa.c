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
struct receive_sa {int /*<<< orphan*/  list; int /*<<< orphan*/  an; int /*<<< orphan*/ * pkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802_1x_kay_deinit_data_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct receive_sa*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee802_1x_kay_deinit_receive_sa(struct receive_sa *psa)
{
	ieee802_1x_kay_deinit_data_key(psa->pkey);
	psa->pkey = NULL;
	wpa_printf(MSG_DEBUG,
		   "KaY: Delete receive SA(an: %hhu) of SC",
		   psa->an);
	dl_list_del(&psa->list);
	os_free(psa);
}