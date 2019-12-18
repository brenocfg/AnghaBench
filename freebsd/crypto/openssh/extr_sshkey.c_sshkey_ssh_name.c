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
struct sshkey {int /*<<< orphan*/  ecdsa_nid; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 char const* sshkey_ssh_name_from_type_nid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
sshkey_ssh_name(const struct sshkey *k)
{
	return sshkey_ssh_name_from_type_nid(k->type, k->ecdsa_nid);
}