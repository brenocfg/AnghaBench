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
struct fs_dev {int dummy; } ;
struct freepool {int offset; int bufsize; int nr_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  FP_CNF (int) ; 
 int /*<<< orphan*/  FP_CNT (int) ; 
 int /*<<< orphan*/  FP_CTU (int) ; 
 int /*<<< orphan*/  FP_EA (int) ; 
 int /*<<< orphan*/  FP_SA (int) ; 
 int /*<<< orphan*/  FS_DEBUG_INIT ; 
 int RBFP_CME ; 
 int RBFP_RBS ; 
 int RBFP_RBSVAL ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_fp(struct fs_dev *dev, struct freepool *fp, int queue,
		   int bufsize, int nr_buffers)
{
	func_enter ();

	fs_dprintk (FS_DEBUG_INIT, "Initializing free pool at %x:\n", queue);

	write_fs (dev, FP_CNF(queue), (bufsize * RBFP_RBS) | RBFP_RBSVAL | RBFP_CME);
	write_fs (dev, FP_SA(queue),  0);
	write_fs (dev, FP_EA(queue),  0);
	write_fs (dev, FP_CTU(queue), 0);
	write_fs (dev, FP_CNT(queue), 0);

	fp->offset = queue; 
	fp->bufsize = bufsize;
	fp->nr_buffers = nr_buffers;

	func_exit ();
	return 1;
}