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
struct eap_method {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct eap_method*) ; 

__attribute__((used)) static void eap_server_method_free(struct eap_method *method)
{
	os_free(method);
}