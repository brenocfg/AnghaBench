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
struct dn_id {int len; int type; uintptr_t id; scalar_t__ subtype; } ;

/* Variables and functions */

__attribute__((used)) static void
oid_fill(struct dn_id *oid, int len, int type, uintptr_t id)
{
	oid->len = len;
	oid->type = type;
	oid->subtype = 0;
	oid->id = id;
}