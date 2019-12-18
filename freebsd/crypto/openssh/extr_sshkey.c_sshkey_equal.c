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
struct sshkey {scalar_t__ type; int /*<<< orphan*/  cert; } ;

/* Variables and functions */
 int /*<<< orphan*/  cert_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sshkey_equal_public (struct sshkey const*,struct sshkey const*) ; 
 scalar_t__ sshkey_is_cert (struct sshkey const*) ; 

int
sshkey_equal(const struct sshkey *a, const struct sshkey *b)
{
	if (a == NULL || b == NULL || a->type != b->type)
		return 0;
	if (sshkey_is_cert(a)) {
		if (!cert_compare(a->cert, b->cert))
			return 0;
	}
	return sshkey_equal_public(a, b);
}