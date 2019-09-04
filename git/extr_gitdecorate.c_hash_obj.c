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
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct object {TYPE_1__ oid; } ;

/* Variables and functions */
 unsigned int sha1hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int hash_obj(const struct object *obj, unsigned int n)
{
	return sha1hash(obj->oid.hash) % n;
}