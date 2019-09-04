#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parsed_objects; int /*<<< orphan*/  objects; int /*<<< orphan*/ * index; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HASH_SHA1 ; 
 int /*<<< orphan*/  parsed_object_pool_new () ; 
 int /*<<< orphan*/  raw_object_store_new () ; 
 int /*<<< orphan*/  repo_set_hash_algo (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_index ; 
 TYPE_1__ the_repo ; 
 TYPE_1__* the_repository ; 

void initialize_the_repository(void)
{
	the_repository = &the_repo;

	the_repo.index = &the_index;
	the_repo.objects = raw_object_store_new();
	the_repo.parsed_objects = parsed_object_pool_new();

	repo_set_hash_algo(&the_repo, GIT_HASH_SHA1);
}