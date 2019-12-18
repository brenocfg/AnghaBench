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
struct eap_pwd_data {scalar_t__ state; int /*<<< orphan*/  session_id; } ;

/* Variables and functions */
 int SHA256_MAC_LEN ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 * eap_pwd_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_pwd_data *data = priv;
	u8 *id;

	if (data->state != SUCCESS)
		return NULL;

	id = os_memdup(data->session_id, 1 + SHA256_MAC_LEN);
	if (id == NULL)
		return NULL;

	*len = 1 + SHA256_MAC_LEN;

	return id;
}