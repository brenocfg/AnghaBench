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
struct object_id {int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {int /*<<< orphan*/  rawsz; } ;

/* Variables and functions */
 unsigned int memhash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int strhash (char const*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static unsigned int hash_oid_string(const struct object_id *oid,
				    const char *string)
{
	return memhash(oid->hash, the_hash_algo->rawsz) + strhash(string);
}