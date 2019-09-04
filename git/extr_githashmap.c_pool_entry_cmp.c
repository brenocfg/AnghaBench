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
struct pool_entry {unsigned char const* data; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,scalar_t__) ; 

__attribute__((used)) static int pool_entry_cmp(const void *unused_cmp_data,
			  const struct pool_entry *e1,
			  const struct pool_entry *e2,
			  const unsigned char *keydata)
{
	return e1->data != keydata &&
	       (e1->len != e2->len || memcmp(e1->data, keydata, e1->len));
}