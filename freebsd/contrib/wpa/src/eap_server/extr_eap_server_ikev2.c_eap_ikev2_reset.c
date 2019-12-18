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
struct eap_ikev2_data {int /*<<< orphan*/  ikev2; int /*<<< orphan*/  out_buf; int /*<<< orphan*/  in_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (struct eap_ikev2_data*,int) ; 
 int /*<<< orphan*/  ikev2_initiator_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_ikev2_reset(struct eap_sm *sm, void *priv)
{
	struct eap_ikev2_data *data = priv;
	wpabuf_free(data->in_buf);
	wpabuf_free(data->out_buf);
	ikev2_initiator_deinit(&data->ikev2);
	bin_clear_free(data, sizeof(*data));
}