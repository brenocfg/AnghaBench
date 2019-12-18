#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct timeval {scalar_t__ tv_sec; } ;
struct nvme_io_test_internal {scalar_t__ size; scalar_t__ opc; int flags; scalar_t__ time; int /*<<< orphan*/  td_active; void** io_completed; TYPE_1__* ns; int /*<<< orphan*/  start; int /*<<< orphan*/  td_idx; } ;
struct mtx {int dummy; } ;
struct cdevsw {int /*<<< orphan*/  (* d_strategy ) (struct bio*) ;} ;
struct cdev {struct cdevsw* si_devsw; } ;
struct bio {scalar_t__ bio_bcount; int bio_flags; scalar_t__ bio_resid; void* bio_data; void* bio_offset; struct cdev* bio_dev; int /*<<< orphan*/  bio_done; int /*<<< orphan*/  bio_cmd; } ;
struct TYPE_3__ {struct cdev* cdev; } ;

/* Variables and functions */
 int BIO_ERROR ; 
 int /*<<< orphan*/  BIO_READ ; 
 int /*<<< orphan*/  BIO_WRITE ; 
 int /*<<< orphan*/  M_NVME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ NVME_OPC_READ ; 
 int NVME_TEST_FLAG_REFTHREAD ; 
 int /*<<< orphan*/  PRIBIO ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 struct cdevsw* dev_refthread (struct cdev*,int*) ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  getmicrouptime (struct timeval*) ; 
 int /*<<< orphan*/  kthread_exit () ; 
 void* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memset (struct bio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (struct bio*,struct mtx*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 int /*<<< orphan*/  nvme_ns_bio_test_cb ; 
 int nvme_ns_get_sector_size (TYPE_1__*) ; 
 scalar_t__ nvme_ns_get_size (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (struct bio*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup_one (struct nvme_io_test_internal*) ; 

__attribute__((used)) static void
nvme_ns_bio_test(void *arg)
{
	struct nvme_io_test_internal	*io_test = arg;
	struct cdevsw			*csw;
	struct mtx			*mtx;
	struct bio			*bio;
	struct cdev			*dev;
	void				*buf;
	struct timeval			t;
	uint64_t			io_completed = 0, offset;
	uint32_t			idx;
	int				ref;

	buf = malloc(io_test->size, M_NVME, M_WAITOK);
	idx = atomic_fetchadd_int(&io_test->td_idx, 1);
	dev = io_test->ns->cdev;

	offset = idx * 2048 * nvme_ns_get_sector_size(io_test->ns);

	while (1) {

		bio = g_alloc_bio();

		memset(bio, 0, sizeof(*bio));
		bio->bio_cmd = (io_test->opc == NVME_OPC_READ) ?
		    BIO_READ : BIO_WRITE;
		bio->bio_done = nvme_ns_bio_test_cb;
		bio->bio_dev = dev;
		bio->bio_offset = offset;
		bio->bio_data = buf;
		bio->bio_bcount = io_test->size;

		if (io_test->flags & NVME_TEST_FLAG_REFTHREAD) {
			csw = dev_refthread(dev, &ref);
		} else
			csw = dev->si_devsw;

		mtx = mtx_pool_find(mtxpool_sleep, bio);
		mtx_lock(mtx);
		(*csw->d_strategy)(bio);
		msleep(bio, mtx, PRIBIO, "biotestwait", 0);
		mtx_unlock(mtx);

		if (io_test->flags & NVME_TEST_FLAG_REFTHREAD) {
			dev_relthread(dev, ref);
		}

		if ((bio->bio_flags & BIO_ERROR) || (bio->bio_resid > 0))
			break;

		g_destroy_bio(bio);

		io_completed++;

		getmicrouptime(&t);
		timevalsub(&t, &io_test->start);

		if (t.tv_sec >= io_test->time)
			break;

		offset += io_test->size;
		if ((offset + io_test->size) > nvme_ns_get_size(io_test->ns))
			offset = 0;
	}

	io_test->io_completed[idx] = io_completed;
	wakeup_one(io_test);

	free(buf, M_NVME);

	atomic_subtract_int(&io_test->td_active, 1);
	mb();

	kthread_exit();
}