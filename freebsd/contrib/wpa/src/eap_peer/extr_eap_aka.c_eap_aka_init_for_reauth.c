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
struct eap_aka_data {scalar_t__ num_notification; scalar_t__ num_id_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUE ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void * eap_aka_init_for_reauth(struct eap_sm *sm, void *priv)
{
	struct eap_aka_data *data = priv;
	data->num_id_req = 0;
	data->num_notification = 0;
	eap_aka_state(data, CONTINUE);
	return priv;
}