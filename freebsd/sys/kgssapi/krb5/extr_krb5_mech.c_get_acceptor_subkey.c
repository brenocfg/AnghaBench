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
struct krb5_keyblock {int dummy; } ;
struct krb5_context {int /*<<< orphan*/  kc_local_subkey; int /*<<< orphan*/  kc_remote_subkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_key (int /*<<< orphan*/ *,struct krb5_keyblock**) ; 
 scalar_t__ is_initiator (struct krb5_context*) ; 

__attribute__((used)) static void
get_acceptor_subkey(struct krb5_context *kc, struct krb5_keyblock **kdp)
{

	if (is_initiator(kc))
		copy_key(&kc->kc_remote_subkey, kdp);
	else
		copy_key(&kc->kc_local_subkey, kdp);
}