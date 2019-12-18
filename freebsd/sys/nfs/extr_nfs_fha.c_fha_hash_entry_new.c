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
typedef  int /*<<< orphan*/  u_int64_t ;
struct fha_hash_entry {int /*<<< orphan*/  threads; scalar_t__ num_threads; scalar_t__ num_exclusive; scalar_t__ num_rw; int /*<<< orphan*/  fh; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_NFS_FHA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct fha_hash_entry* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fha_hash_entry *
fha_hash_entry_new(u_int64_t fh)
{
	struct fha_hash_entry *e;

	e = malloc(sizeof(*e), M_NFS_FHA, M_WAITOK);
	e->fh = fh;
	e->num_rw = 0;
	e->num_exclusive = 0;
	e->num_threads = 0;
	LIST_INIT(&e->threads);

	return (e);
}