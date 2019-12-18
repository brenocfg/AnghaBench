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
struct wpa_supplicant {int dummy; } ;
struct gas_query {int /*<<< orphan*/  pending; struct wpa_supplicant* wpa_s; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 struct gas_query* os_zalloc (int) ; 

struct gas_query * gas_query_init(struct wpa_supplicant *wpa_s)
{
	struct gas_query *gas;

	gas = os_zalloc(sizeof(*gas));
	if (gas == NULL)
		return NULL;

	gas->wpa_s = wpa_s;
	dl_list_init(&gas->pending);

	return gas;
}