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
struct revoked_blob {scalar_t__ len; int /*<<< orphan*/  blob; } ;

/* Variables and functions */
 scalar_t__ MINIMUM (scalar_t__,scalar_t__) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
blob_cmp(struct revoked_blob *a, struct revoked_blob *b)
{
	int r;

	if (a->len != b->len) {
		if ((r = memcmp(a->blob, b->blob, MINIMUM(a->len, b->len))) != 0)
			return r;
		return a->len > b->len ? 1 : -1;
	} else
		return memcmp(a->blob, b->blob, a->len);
}