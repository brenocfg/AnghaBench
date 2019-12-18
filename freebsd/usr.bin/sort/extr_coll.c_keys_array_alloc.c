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
struct keys_array {int dummy; } ;

/* Variables and functions */
 size_t keys_array_size () ; 
 int /*<<< orphan*/  memset (struct keys_array*,int /*<<< orphan*/ ,size_t) ; 
 struct keys_array* sort_malloc (size_t) ; 

struct keys_array *
keys_array_alloc(void)
{
	struct keys_array *ka;
	size_t sz;

	sz = keys_array_size();
	ka = sort_malloc(sz);
	memset(ka, 0, sz);

	return (ka);
}