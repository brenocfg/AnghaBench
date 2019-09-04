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
struct packed_git {unsigned int num_bad_objects; scalar_t__ bad_object_sha1; } ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_RAWSZ ; 
 int /*<<< orphan*/  hashcpy (scalar_t__,unsigned char const*) ; 
 scalar_t__ hasheq (unsigned char const*,scalar_t__) ; 
 int /*<<< orphan*/  st_add (unsigned int,int) ; 
 int /*<<< orphan*/  st_mult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* the_hash_algo ; 
 scalar_t__ xrealloc (scalar_t__,int /*<<< orphan*/ ) ; 

void mark_bad_packed_object(struct packed_git *p, const unsigned char *sha1)
{
	unsigned i;
	const unsigned hashsz = the_hash_algo->rawsz;
	for (i = 0; i < p->num_bad_objects; i++)
		if (hasheq(sha1, p->bad_object_sha1 + hashsz * i))
			return;
	p->bad_object_sha1 = xrealloc(p->bad_object_sha1,
				      st_mult(GIT_MAX_RAWSZ,
					      st_add(p->num_bad_objects, 1)));
	hashcpy(p->bad_object_sha1 + hashsz * p->num_bad_objects, sha1);
	p->num_bad_objects++;
}