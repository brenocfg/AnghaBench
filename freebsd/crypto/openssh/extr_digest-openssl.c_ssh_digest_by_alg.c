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
struct ssh_digest {int id; int /*<<< orphan*/ * mdfunc; } ;

/* Variables and functions */
 int SSH_DIGEST_MAX ; 
 struct ssh_digest const* digests ; 

__attribute__((used)) static const struct ssh_digest *
ssh_digest_by_alg(int alg)
{
	if (alg < 0 || alg >= SSH_DIGEST_MAX)
		return NULL;
	if (digests[alg].id != alg) /* sanity */
		return NULL;
	if (digests[alg].mdfunc == NULL)
		return NULL;
	return &(digests[alg]);
}