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
typedef  int /*<<< orphan*/  uint32_t ;
struct fhashentry6 {int dummy; } ;
struct fhashentry4 {int dummy; } ;
struct fhashentry {scalar_t__ af; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  hash_flow4 (struct fhashentry4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_flow6 (struct fhashentry6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
hash_flow_ent(struct fhashentry *ent, uint32_t size)
{
	uint32_t hash;

	if (ent->af == AF_INET) {
		hash = hash_flow4((struct fhashentry4 *)ent, size);
	} else {
		hash = hash_flow6((struct fhashentry6 *)ent, size);
	}

	return (hash);
}