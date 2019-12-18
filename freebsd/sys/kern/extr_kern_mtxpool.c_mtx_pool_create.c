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
struct mtx_pool {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MTXPOOL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct mtx_pool* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_pool_initialize (struct mtx_pool*,char const*,int,int) ; 
 int /*<<< orphan*/  powerof2 (int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

struct mtx_pool *
mtx_pool_create(const char *mtx_name, int pool_size, int opts)
{
	struct mtx_pool *pool;

	if (pool_size <= 0 || !powerof2(pool_size)) {
		printf("WARNING: %s pool size is not a power of 2.\n",
		    mtx_name);
		pool_size = 128;
	}
	pool = malloc(sizeof (struct mtx_pool) +
	    ((pool_size - 1) * sizeof (struct mtx)),
	    M_MTXPOOL, M_WAITOK | M_ZERO);
	mtx_pool_initialize(pool, mtx_name, pool_size, opts);
	return pool;
}