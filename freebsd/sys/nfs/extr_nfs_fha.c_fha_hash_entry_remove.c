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
struct fha_hash_entry {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct fha_hash_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  fha_hash_entry_destroy (struct fha_hash_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fha_hash_entry_remove(struct fha_hash_entry *e)
{

	mtx_assert(e->mtx, MA_OWNED);
	LIST_REMOVE(e, link);
	fha_hash_entry_destroy(e);
}