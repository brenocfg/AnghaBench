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
typedef  scalar_t__ keyid_t ;

/* Variables and functions */
 scalar_t__ cache_flags ; 
 int /*<<< orphan*/ * cache_keyacclist ; 
 scalar_t__ cache_keyid ; 
 int /*<<< orphan*/ * cache_secret ; 
 scalar_t__ cache_secretsize ; 
 scalar_t__ cache_type ; 

__attribute__((used)) static void
authcache_flush_id(
	keyid_t id
	)
{
	if (cache_keyid == id) {
		cache_keyid = 0;
		cache_type = 0;
		cache_flags = 0;
		cache_secret = NULL;
		cache_secretsize = 0;
		cache_keyacclist = NULL;
	}
}