#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* digests ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int
ssh_digest_alg_by_name(const char *name)
{
	int alg;

	for (alg = 0; digests[alg].id != -1; alg++) {
		if (strcasecmp(name, digests[alg].name) == 0)
			return digests[alg].id;
	}
	return -1;
}