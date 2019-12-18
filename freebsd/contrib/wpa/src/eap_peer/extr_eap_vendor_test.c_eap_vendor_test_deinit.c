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
struct eap_vendor_test_data {int dummy; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct eap_vendor_test_data*) ; 

__attribute__((used)) static void eap_vendor_test_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_vendor_test_data *data = priv;
	os_free(data);
}