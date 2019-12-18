#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct untracked_cache_dir {TYPE_1__ exclude_oid; } ;
struct read_data {scalar_t__ data; scalar_t__ end; struct untracked_cache_dir** ucd; } ;
struct TYPE_4__ {scalar_t__ rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static void read_oid(size_t pos, void *cb)
{
	struct read_data *rd = cb;
	struct untracked_cache_dir *ud = rd->ucd[pos];
	if (rd->data + the_hash_algo->rawsz > rd->end) {
		rd->data = rd->end + 1;
		return;
	}
	hashcpy(ud->exclude_oid.hash, rd->data);
	rd->data += the_hash_algo->rawsz;
}