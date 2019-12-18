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
struct wpa_supplicant {TYPE_1__* driver; int /*<<< orphan*/  global_drv_priv; } ;
struct TYPE_2__ {void* (* init2 ) (struct wpa_supplicant*,char const*,int /*<<< orphan*/ ) ;void* (* init ) (struct wpa_supplicant*,char const*) ;} ;

/* Variables and functions */
 void* stub1 (struct wpa_supplicant*,char const*,int /*<<< orphan*/ ) ; 
 void* stub2 (struct wpa_supplicant*,char const*) ; 

__attribute__((used)) static inline void * wpa_drv_init(struct wpa_supplicant *wpa_s,
				  const char *ifname)
{
	if (wpa_s->driver->init2)
		return wpa_s->driver->init2(wpa_s, ifname,
					    wpa_s->global_drv_priv);
	if (wpa_s->driver->init) {
		return wpa_s->driver->init(wpa_s, ifname);
	}
	return NULL;
}