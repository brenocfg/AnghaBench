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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct trust_anchor {struct ta_key* keylist; } ;
struct ta_key {scalar_t__ type; size_t len; int /*<<< orphan*/  data; struct ta_key* next; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static struct ta_key*
anchor_find_key(struct trust_anchor* ta, uint8_t* rdata, size_t rdata_len,
	uint16_t type)
{
	struct ta_key* k;
	for(k = ta->keylist; k; k = k->next) {
		if(k->type == type && k->len == rdata_len &&
			memcmp(k->data, rdata, rdata_len) == 0)
			return k;
	}
	return NULL;
}