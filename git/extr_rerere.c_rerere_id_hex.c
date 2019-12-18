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
struct rerere_id {TYPE_1__* collection; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 char const* hash_to_hex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *rerere_id_hex(const struct rerere_id *id)
{
	return hash_to_hex(id->collection->hash);
}