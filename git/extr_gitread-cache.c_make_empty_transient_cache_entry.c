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
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_size (size_t) ; 
 struct cache_entry* xcalloc (int,int /*<<< orphan*/ ) ; 

struct cache_entry *make_empty_transient_cache_entry(size_t len)
{
	return xcalloc(1, cache_entry_size(len));
}