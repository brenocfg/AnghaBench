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
struct ewah_bitmap {int dummy; } ;
typedef  scalar_t__ khiter_t ;
struct TYPE_2__ {int /*<<< orphan*/  reused; } ;

/* Variables and functions */
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get_sha1 (int /*<<< orphan*/ ,unsigned char const*) ; 
 struct ewah_bitmap* kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ writer ; 

__attribute__((used)) static struct ewah_bitmap *find_reused_bitmap(const unsigned char *sha1)
{
	khiter_t hash_pos;

	if (!writer.reused)
		return NULL;

	hash_pos = kh_get_sha1(writer.reused, sha1);
	if (hash_pos >= kh_end(writer.reused))
		return NULL;

	return kh_value(writer.reused, hash_pos);
}