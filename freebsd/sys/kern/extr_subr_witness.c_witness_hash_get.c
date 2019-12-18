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
typedef  size_t uint32_t ;
struct witness {struct witness* w_hash_next; int /*<<< orphan*/  w_name; } ;
struct TYPE_2__ {size_t wh_size; struct witness** wh_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__ w_hash ; 
 int /*<<< orphan*/  w_mtx ; 
 scalar_t__ witness_cold ; 
 size_t witness_hash_djb2 (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct witness *
witness_hash_get(const char *key)
{
	struct witness *w;
	uint32_t hash;
	
	MPASS(key != NULL);
	if (witness_cold == 0)
		mtx_assert(&w_mtx, MA_OWNED);
	hash = witness_hash_djb2(key, 0) % w_hash.wh_size;
	w = w_hash.wh_array[hash];
	while (w != NULL) {
		if (strcmp(w->w_name, key) == 0)
			goto out;
		w = w->w_hash_next;
	}

out:
	return (w);
}