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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  a6; int /*<<< orphan*/  a4; } ;
struct chashentry {TYPE_1__ a; } ;

/* Variables and functions */
 int AF_INET ; 
 scalar_t__ hash_ip (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hash_ip6 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hash_ip64 (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static uint32_t
hash_ent(struct chashentry *ent, int af, int mlen, uint32_t size)
{
	uint32_t hash;

	hash = 0;

	if (af == AF_INET) {
#ifdef INET
		hash = hash_ip(ent->a.a4, size);
#endif
	} else {
#ifdef INET6
		if (mlen == 64)
			hash = hash_ip64(&ent->a.a6, size);
		else
			hash = hash_ip6(&ent->a.a6, size);
#endif
	}

	return (hash);
}