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
struct signature_check {int /*<<< orphan*/  primary_key_fingerprint; int /*<<< orphan*/  fingerprint; int /*<<< orphan*/  key; int /*<<< orphan*/  signer; int /*<<< orphan*/  gpg_status; int /*<<< orphan*/  gpg_output; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 

void signature_check_clear(struct signature_check *sigc)
{
	FREE_AND_NULL(sigc->payload);
	FREE_AND_NULL(sigc->gpg_output);
	FREE_AND_NULL(sigc->gpg_status);
	FREE_AND_NULL(sigc->signer);
	FREE_AND_NULL(sigc->key);
	FREE_AND_NULL(sigc->fingerprint);
	FREE_AND_NULL(sigc->primary_key_fingerprint);
}