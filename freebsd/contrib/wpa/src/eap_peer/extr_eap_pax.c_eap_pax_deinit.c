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
struct eap_pax_data {int /*<<< orphan*/  cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (struct eap_pax_data*,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_pax_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_pax_data *data = priv;
	os_free(data->cid);
	bin_clear_free(data, sizeof(*data));
}