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
struct eap_fast_data {int success; int /*<<< orphan*/  emsk; int /*<<< orphan*/  simck; int /*<<< orphan*/  key_data; } ;

/* Variables and functions */
 scalar_t__ eap_fast_derive_eap_emsk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_fast_derive_eap_msk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_fast_derive_msk(struct eap_fast_data *data)
{
	if (eap_fast_derive_eap_msk(data->simck, data->key_data) < 0 ||
	    eap_fast_derive_eap_emsk(data->simck, data->emsk) < 0)
		return -1;
	data->success = 1;
	return 0;
}