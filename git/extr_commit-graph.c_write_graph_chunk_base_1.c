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
struct hashfile {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct commit_graph {TYPE_1__ oid; struct commit_graph* base_graph; } ;
struct TYPE_4__ {int /*<<< orphan*/  rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashwrite (struct hashfile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static int write_graph_chunk_base_1(struct hashfile *f,
				    struct commit_graph *g)
{
	int num = 0;

	if (!g)
		return 0;

	num = write_graph_chunk_base_1(f, g->base_graph);
	hashwrite(f, g->oid.hash, the_hash_algo->rawsz);
	return num + 1;
}