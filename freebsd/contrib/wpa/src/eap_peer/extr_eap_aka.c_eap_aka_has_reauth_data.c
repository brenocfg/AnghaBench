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
struct eap_sm {int dummy; } ;
struct eap_aka_data {scalar_t__ reauth_id; scalar_t__ pseudonym; } ;
typedef  int Boolean ;

/* Variables and functions */

__attribute__((used)) static Boolean eap_aka_has_reauth_data(struct eap_sm *sm, void *priv)
{
	struct eap_aka_data *data = priv;
	return data->pseudonym || data->reauth_id;
}