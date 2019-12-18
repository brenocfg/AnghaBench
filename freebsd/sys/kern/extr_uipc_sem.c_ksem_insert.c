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
struct ksem_mapping {char* km_path; int /*<<< orphan*/  km_ksem; int /*<<< orphan*/  km_fnv; } ;
struct ksem {char* ks_path; } ;
typedef  int /*<<< orphan*/  Fnv32_t ;

/* Variables and functions */
 int /*<<< orphan*/  KSEM_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct ksem_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_KSEM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  km_link ; 
 int /*<<< orphan*/  ksem_hold (struct ksem*) ; 
 struct ksem_mapping* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ksem_insert(char *path, Fnv32_t fnv, struct ksem *ks)
{
	struct ksem_mapping *map;

	map = malloc(sizeof(struct ksem_mapping), M_KSEM, M_WAITOK);
	map->km_path = path;
	map->km_fnv = fnv;
	map->km_ksem = ksem_hold(ks);
	ks->ks_path = path;
	LIST_INSERT_HEAD(KSEM_HASH(fnv), map, km_link);
}