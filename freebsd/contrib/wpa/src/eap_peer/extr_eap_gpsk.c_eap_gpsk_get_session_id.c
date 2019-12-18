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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct eap_gpsk_data {scalar_t__ state; size_t id_len; int /*<<< orphan*/  session_id; } ;

/* Variables and functions */
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static u8 * eap_gpsk_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_gpsk_data *data = priv;
	u8 *sid;

	if (data->state != SUCCESS)
		return NULL;

	sid = os_memdup(data->session_id, data->id_len);
	if (sid == NULL)
		return NULL;
	*len = data->id_len;

	return sid;
}