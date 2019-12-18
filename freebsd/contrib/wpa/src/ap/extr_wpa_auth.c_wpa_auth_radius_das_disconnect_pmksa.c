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
struct wpa_authenticator {int /*<<< orphan*/  pmksa; } ;
struct radius_das_attrs {int dummy; } ;

/* Variables and functions */
 int pmksa_cache_auth_radius_das_disconnect (int /*<<< orphan*/ ,struct radius_das_attrs*) ; 

int wpa_auth_radius_das_disconnect_pmksa(struct wpa_authenticator *wpa_auth,
					 struct radius_das_attrs *attr)
{
	return pmksa_cache_auth_radius_das_disconnect(wpa_auth->pmksa, attr);
}