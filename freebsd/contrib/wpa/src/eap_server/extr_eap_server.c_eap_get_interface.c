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
struct eap_eapol_interface {int dummy; } ;
struct eap_sm {struct eap_eapol_interface eap_if; } ;

/* Variables and functions */

struct eap_eapol_interface * eap_get_interface(struct eap_sm *sm)
{
	return &sm->eap_if;
}