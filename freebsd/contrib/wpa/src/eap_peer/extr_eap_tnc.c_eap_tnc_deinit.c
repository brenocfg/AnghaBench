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
struct eap_tnc_data {int /*<<< orphan*/  tncc; int /*<<< orphan*/  out_buf; int /*<<< orphan*/  in_buf; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct eap_tnc_data*) ; 
 int /*<<< orphan*/  tncc_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_tnc_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_tnc_data *data = priv;

	wpabuf_free(data->in_buf);
	wpabuf_free(data->out_buf);
	tncc_deinit(data->tncc);
	os_free(data);
}