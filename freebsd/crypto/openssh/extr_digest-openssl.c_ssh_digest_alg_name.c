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
struct ssh_digest {char const* name; } ;

/* Variables and functions */
 struct ssh_digest* ssh_digest_by_alg (int) ; 

const char *
ssh_digest_alg_name(int alg)
{
	const struct ssh_digest *digest = ssh_digest_by_alg(alg);

	return digest == NULL ? NULL : digest->name;
}