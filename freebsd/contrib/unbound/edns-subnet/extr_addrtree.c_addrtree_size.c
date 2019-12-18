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
struct addrtree {size_t size_bytes; } ;

/* Variables and functions */

inline size_t
addrtree_size(const struct addrtree *tree)
{
	return tree?tree->size_bytes:0;
}