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
struct TYPE_2__ {scalar_t__ rawsz; } ;

/* Variables and functions */
 scalar_t__ GIT_MAX_RAWSZ ; 
 scalar_t__ GIT_SHA1_RAWSZ ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,unsigned char const*,scalar_t__) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static inline int hasheq(const unsigned char *sha1, const unsigned char *sha2)
{
	/*
	 * We write this here instead of deferring to hashcmp so that the
	 * compiler can properly inline it and avoid calling memcmp.
	 */
	if (the_hash_algo->rawsz == GIT_MAX_RAWSZ)
		return !memcmp(sha1, sha2, GIT_MAX_RAWSZ);
	return !memcmp(sha1, sha2, GIT_SHA1_RAWSZ);
}