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
struct hashmap {int dummy; } ;

/* Variables and functions */
 int LAZY_MAX_MUTEX ; 
 int hashmap_bucket (struct hashmap const*,unsigned int) ; 

__attribute__((used)) static inline int compute_dir_lock_nr(
	const struct hashmap *map,
	unsigned int hash)
{
	return hashmap_bucket(map, hash) % LAZY_MAX_MUTEX;
}