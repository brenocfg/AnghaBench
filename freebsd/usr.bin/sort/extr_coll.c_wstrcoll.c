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
struct key_value {int /*<<< orphan*/  k; } ;

/* Variables and functions */
 int BWSLEN (int /*<<< orphan*/ ) ; 
 int bwscoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bwsprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ debug_sort ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
wstrcoll(struct key_value *kv1, struct key_value *kv2, size_t offset)
{

	if (debug_sort) {
		if (offset)
			printf("; offset=%d\n", (int) offset);
		bwsprintf(stdout, kv1->k, "; k1=<", ">");
		printf("(%zu)", BWSLEN(kv1->k));
		bwsprintf(stdout, kv2->k, ", k2=<", ">");
		printf("(%zu)", BWSLEN(kv2->k));
	}

	return (bwscoll(kv1->k, kv2->k, offset));
}