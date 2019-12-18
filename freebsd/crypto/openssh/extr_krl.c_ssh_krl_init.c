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
struct ssh_krl {int /*<<< orphan*/  revoked_certs; int /*<<< orphan*/  revoked_sha1s; int /*<<< orphan*/  revoked_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct ssh_krl* calloc (int,int) ; 

struct ssh_krl *
ssh_krl_init(void)
{
	struct ssh_krl *krl;

	if ((krl = calloc(1, sizeof(*krl))) == NULL)
		return NULL;
	RB_INIT(&krl->revoked_keys);
	RB_INIT(&krl->revoked_sha1s);
	TAILQ_INIT(&krl->revoked_certs);
	return krl;
}