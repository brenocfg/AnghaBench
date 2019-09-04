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
struct object_id {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int get_sha1_hex (char const*,int /*<<< orphan*/ ) ; 

int get_oid_hex(const char *hex, struct object_id *oid)
{
	return get_sha1_hex(hex, oid->hash);
}