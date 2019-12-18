#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  fileHandle_t ;
struct TYPE_4__ {int size; unsigned char* reachabilities; } ;
typedef  TYPE_1__ aas_routingcache_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* FS_Read ) (unsigned char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ GetMemory (int) ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  stub1 (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,int,int /*<<< orphan*/ ) ; 

aas_routingcache_t *AAS_ReadCache(fileHandle_t fp)
{
	int size;
	aas_routingcache_t *cache;

	botimport.FS_Read(&size, sizeof(size), fp);
	cache = (aas_routingcache_t *) GetMemory(size);
	cache->size = size;
	botimport.FS_Read((unsigned char *)cache + sizeof(size), size - sizeof(size), fp);
	cache->reachabilities = (unsigned char *) cache + sizeof(aas_routingcache_t) - sizeof(unsigned short) +
		(size - sizeof(aas_routingcache_t) + sizeof(unsigned short)) / 3 * 2;
	return cache;
}