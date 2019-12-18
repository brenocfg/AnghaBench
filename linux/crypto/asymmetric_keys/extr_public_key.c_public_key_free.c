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
struct public_key {struct public_key* params; struct public_key* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct public_key*) ; 

void public_key_free(struct public_key *key)
{
	if (key) {
		kfree(key->key);
		kfree(key->params);
		kfree(key);
	}
}