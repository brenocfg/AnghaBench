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
struct object_id {int /*<<< orphan*/  hash; } ;
struct commit_name {int dummy; } ;

/* Variables and functions */
 struct commit_name* hashmap_get_from_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  names ; 
 int /*<<< orphan*/  sha1hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct commit_name *find_commit_name(const struct object_id *peeled)
{
	return hashmap_get_from_hash(&names, sha1hash(peeled->hash), peeled->hash);
}