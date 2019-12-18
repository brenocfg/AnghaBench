#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ km_elem; } ;
struct krb5_context {int /*<<< orphan*/  kc_lock; scalar_t__ kc_recv_sign_Kc; scalar_t__ kc_recv_seal_Kc; scalar_t__ kc_recv_seal_Ki; scalar_t__ kc_recv_seal_Ke; scalar_t__ kc_send_sign_Kc; scalar_t__ kc_send_seal_Kc; scalar_t__ kc_send_seal_Ki; scalar_t__ kc_send_seal_Ke; scalar_t__ kc_checksumkey; scalar_t__ kc_encryptkey; scalar_t__ kc_tokenkey; TYPE_1__ kc_msg_order; int /*<<< orphan*/  kc_target_name; int /*<<< orphan*/  kc_source_name; int /*<<< orphan*/  kc_remote_subkey; int /*<<< orphan*/  kc_local_subkey; int /*<<< orphan*/  kc_keyblock; int /*<<< orphan*/  kc_remote_address; int /*<<< orphan*/  kc_local_address; } ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  TYPE_2__* gss_buffer_t ;
struct TYPE_5__ {int /*<<< orphan*/ * value; scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  delete_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_keyblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_key (scalar_t__) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
krb5_delete(gss_ctx_id_t ctx, gss_buffer_t output_token)
{
	struct krb5_context *kc = (struct krb5_context *)ctx;

	delete_address(&kc->kc_local_address);
	delete_address(&kc->kc_remote_address);
	delete_keyblock(&kc->kc_keyblock);
	delete_keyblock(&kc->kc_local_subkey);
	delete_keyblock(&kc->kc_remote_subkey);
	delete_data(&kc->kc_source_name);
	delete_data(&kc->kc_target_name);
	if (kc->kc_msg_order.km_elem)
		free(kc->kc_msg_order.km_elem, M_GSSAPI);
	if (output_token) {
		output_token->length = 0;
		output_token->value = NULL;
	}
	if (kc->kc_tokenkey) {
		krb5_free_key(kc->kc_tokenkey);
		if (kc->kc_encryptkey) {
			krb5_free_key(kc->kc_encryptkey);
			krb5_free_key(kc->kc_checksumkey);
		} else {
			krb5_free_key(kc->kc_send_seal_Ke);
			krb5_free_key(kc->kc_send_seal_Ki);
			krb5_free_key(kc->kc_send_seal_Kc);
			krb5_free_key(kc->kc_send_sign_Kc);
			krb5_free_key(kc->kc_recv_seal_Ke);
			krb5_free_key(kc->kc_recv_seal_Ki);
			krb5_free_key(kc->kc_recv_seal_Kc);
			krb5_free_key(kc->kc_recv_sign_Kc);
		}
	}
	mtx_destroy(&kc->kc_lock);
}