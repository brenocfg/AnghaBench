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
typedef  int /*<<< orphan*/  uint16_t ;
struct ta_key {size_t len; int /*<<< orphan*/  type; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ta_key*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (struct ta_key*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ta_key*
anchor_new_ta_key(uint8_t* rdata, size_t rdata_len, uint16_t type)
{
	struct ta_key* k = (struct ta_key*)malloc(sizeof(*k));
	if(!k)
		return NULL;
	memset(k, 0, sizeof(*k));
	k->data = memdup(rdata, rdata_len);
	if(!k->data) {
		free(k);
		return NULL;
	}
	k->len = rdata_len;
	k->type = type;
	return k;
}