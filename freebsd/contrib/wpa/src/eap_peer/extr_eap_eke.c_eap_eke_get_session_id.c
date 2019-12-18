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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct TYPE_2__ {int nonce_len; } ;
struct eap_eke_data {scalar_t__ state; TYPE_1__ sess; int /*<<< orphan*/  nonce_s; int /*<<< orphan*/  nonce_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_EKE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 * eap_eke_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_eke_data *data = priv;
	u8 *sid;
	size_t sid_len;

	if (data->state != SUCCESS)
		return NULL;

	sid_len = 1 + 2 * data->sess.nonce_len;
	sid = os_malloc(sid_len);
	if (sid == NULL)
		return NULL;
	sid[0] = EAP_TYPE_EKE;
	os_memcpy(sid + 1, data->nonce_p, data->sess.nonce_len);
	os_memcpy(sid + 1 + data->sess.nonce_len, data->nonce_s,
		  data->sess.nonce_len);
	*len = sid_len;

	return sid;
}