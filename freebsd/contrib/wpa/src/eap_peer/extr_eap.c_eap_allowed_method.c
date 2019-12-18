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
typedef  int /*<<< orphan*/  u32 ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int eap_config_allowed_method (struct eap_sm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_get_config (struct eap_sm*) ; 

int eap_allowed_method(struct eap_sm *sm, int vendor, u32 method)
{
	return eap_config_allowed_method(sm, eap_get_config(sm), vendor,
					 method);
}