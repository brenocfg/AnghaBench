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
typedef  int /*<<< orphan*/  uint64_t ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct fuse_forget_in {int /*<<< orphan*/  nlookup; } ;
struct fuse_dispatcher {int /*<<< orphan*/  tick; struct fuse_forget_in* indata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_FORGET ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct mount*,int /*<<< orphan*/ ,struct thread*,struct ucred*) ; 
 int /*<<< orphan*/  fuse_insert_message (int /*<<< orphan*/ ,int) ; 

void
fuse_internal_forget_send(struct mount *mp,
    struct thread *td,
    struct ucred *cred,
    uint64_t nodeid,
    uint64_t nlookup)
{

	struct fuse_dispatcher fdi;
	struct fuse_forget_in *ffi;

	/*
         * KASSERT(nlookup > 0, ("zero-times forget for vp #%llu",
         *         (long long unsigned) nodeid));
         */

	fdisp_init(&fdi, sizeof(*ffi));
	fdisp_make(&fdi, FUSE_FORGET, mp, nodeid, td, cred);

	ffi = fdi.indata;
	ffi->nlookup = nlookup;

	fuse_insert_message(fdi.tick, false);
	fdisp_destroy(&fdi);
}