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
struct thread {int dummy; } ;
struct fuse_init_in {int flags; int /*<<< orphan*/  max_readahead; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct fuse_dispatcher {int /*<<< orphan*/  tick; struct fuse_init_in* indata; } ;
struct fuse_data {int /*<<< orphan*/  mp; } ;

/* Variables and functions */
 int FUSE_ASYNC_READ ; 
 int FUSE_BIG_WRITES ; 
 int FUSE_EXPORT_SUPPORT ; 
 int /*<<< orphan*/  FUSE_INIT ; 
 int /*<<< orphan*/  FUSE_KERNEL_MINOR_VERSION ; 
 int /*<<< orphan*/  FUSE_KERNEL_VERSION ; 
 int FUSE_POSIX_LOCKS ; 
 int FUSE_WRITEBACK_CACHE ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make (struct fuse_dispatcher*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_insert_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_insert_message (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_internal_init_callback ; 
 int /*<<< orphan*/  maxbcachebuf ; 

void
fuse_internal_send_init(struct fuse_data *data, struct thread *td)
{
	struct fuse_init_in *fiii;
	struct fuse_dispatcher fdi;

	fdisp_init(&fdi, sizeof(*fiii));
	fdisp_make(&fdi, FUSE_INIT, data->mp, 0, td, NULL);
	fiii = fdi.indata;
	fiii->major = FUSE_KERNEL_VERSION;
	fiii->minor = FUSE_KERNEL_MINOR_VERSION;
	/* 
	 * fusefs currently reads ahead no more than one cache block at a time.
	 * See fuse_read_biobackend
	 */
	fiii->max_readahead = maxbcachebuf;
	/*
	 * Unsupported features:
	 * FUSE_FILE_OPS: No known FUSE server or client supports it
	 * FUSE_ATOMIC_O_TRUNC: our VFS cannot support it
	 * FUSE_DONT_MASK: unlike Linux, FreeBSD always applies the umask, even
	 *	when default ACLs are in use.
	 * FUSE_SPLICE_WRITE, FUSE_SPLICE_MOVE, FUSE_SPLICE_READ: FreeBSD
	 *	doesn't have splice(2).
	 * FUSE_FLOCK_LOCKS: not yet implemented
	 * FUSE_HAS_IOCTL_DIR: not yet implemented
	 * FUSE_AUTO_INVAL_DATA: not yet implemented
	 * FUSE_DO_READDIRPLUS: not yet implemented
	 * FUSE_READDIRPLUS_AUTO: not yet implemented
	 * FUSE_ASYNC_DIO: not yet implemented
	 * FUSE_NO_OPEN_SUPPORT: not yet implemented
	 */
	fiii->flags = FUSE_ASYNC_READ | FUSE_POSIX_LOCKS | FUSE_EXPORT_SUPPORT
		| FUSE_BIG_WRITES | FUSE_WRITEBACK_CACHE;

	fuse_insert_callback(fdi.tick, fuse_internal_init_callback);
	fuse_insert_message(fdi.tick, false);
	fdisp_destroy(&fdi);
}