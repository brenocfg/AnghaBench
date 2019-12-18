#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct syncache_head {int dummy; } ;
struct in_conninfo {int /*<<< orphan*/  inc_ie; } ;
struct TYPE_2__ {size_t hashmask; struct syncache_head* hashbase; int /*<<< orphan*/  hash_secret; } ;

/* Variables and functions */
 TYPE_1__ V_tcp_syncache ; 
 size_t jenkins_hash32 (size_t*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct syncache_head *
syncache_hashbucket(struct in_conninfo *inc)
{
	uint32_t hash;

	/*
	 * The hash is built on foreign port + local port + foreign address.
	 * We rely on the fact that struct in_conninfo starts with 16 bits
	 * of foreign port, then 16 bits of local port then followed by 128
	 * bits of foreign address.  In case of IPv4 address, the first 3
	 * 32-bit words of the address always are zeroes.
	 */
	hash = jenkins_hash32((uint32_t *)&inc->inc_ie, 5,
	    V_tcp_syncache.hash_secret) & V_tcp_syncache.hashmask;

	return (&V_tcp_syncache.hashbase[hash]);
}