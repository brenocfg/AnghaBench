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
struct eap_fast_data {size_t id_len; int /*<<< orphan*/  session_id; int /*<<< orphan*/  success; } ;

/* Variables and functions */
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static u8 * eap_fast_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_fast_data *data = priv;
	u8 *id;

	if (!data->success || !data->session_id)
		return NULL;

	id = os_memdup(data->session_id, data->id_len);
	if (id == NULL)
		return NULL;

	*len = data->id_len;

	return id;
}