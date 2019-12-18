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
struct tpm_key {scalar_t__ blob_len; struct tpm_key* blob; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tpm_key*) ; 

__attribute__((used)) static void asym_tpm_destroy(void *payload0, void *payload3)
{
	struct tpm_key *tk = payload0;

	if (!tk)
		return;

	kfree(tk->blob);
	tk->blob_len = 0;

	kfree(tk);
}