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
struct ikev2_initiator_data {int /*<<< orphan*/  key_pad; int /*<<< orphan*/  r_sign_msg; int /*<<< orphan*/  i_sign_msg; int /*<<< orphan*/  shared_secret; int /*<<< orphan*/  IDr; int /*<<< orphan*/  IDi; int /*<<< orphan*/  i_dh_private; int /*<<< orphan*/  r_dh_public; int /*<<< orphan*/  keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  ikev2_free_keys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void ikev2_initiator_deinit(struct ikev2_initiator_data *data)
{
	ikev2_free_keys(&data->keys);
	wpabuf_free(data->r_dh_public);
	wpabuf_free(data->i_dh_private);
	os_free(data->IDi);
	os_free(data->IDr);
	os_free(data->shared_secret);
	wpabuf_free(data->i_sign_msg);
	wpabuf_free(data->r_sign_msg);
	os_free(data->key_pad);
}