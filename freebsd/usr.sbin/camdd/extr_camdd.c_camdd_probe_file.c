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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct camdd_io_opts {scalar_t__ blocksize; scalar_t__ dev_name; int queue_depth; int offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
struct camdd_dev_file {int fd; scalar_t__ filename; int file_type; int file_flags; TYPE_2__ sb; } ;
struct TYPE_3__ {struct camdd_dev_file file; } ;
struct camdd_dev {scalar_t__ device_name; scalar_t__ blocksize; int sector_size; int start_offset_bytes; int /*<<< orphan*/  max_sector; int /*<<< orphan*/ * fetch; int /*<<< orphan*/  run; int /*<<< orphan*/  target_queue_depth; TYPE_1__ dev_spec; } ;
typedef  unsigned int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAMDD_DEV_FILE ; 
 int CAMDD_FF_CAN_SEEK ; 
 scalar_t__ CAMDD_FILE_DEFAULT_BLOCK ; 
 int /*<<< orphan*/  CAMDD_FILE_DEFAULT_DEPTH ; 
#define  CAMDD_FILE_DISK 131 
#define  CAMDD_FILE_MEM 130 
 int CAMDD_FILE_PIPE ; 
#define  CAMDD_FILE_REG 129 
#define  CAMDD_FILE_TAPE 128 
 int CAMDD_FILE_TTY ; 
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int D_DISK ; 
 int D_MEM ; 
 int D_TAPE ; 
 int D_TTY ; 
 int /*<<< orphan*/  FIODTYPE ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct camdd_dev* camdd_alloc_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  camdd_file_run ; 
 int /*<<< orphan*/  camdd_free_dev (struct camdd_dev*) ; 
 int camdd_probe_tape (int,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  err (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__,...) ; 
 int fstat (int,TYPE_2__*) ; 
 int ioctl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  warnx (char*,int,scalar_t__,...) ; 

struct camdd_dev *
camdd_probe_file(int fd, struct camdd_io_opts *io_opts, int retry_count,
    int timeout)
{
	struct camdd_dev *dev = NULL;
	struct camdd_dev_file *file_dev;
	uint64_t blocksize = io_opts->blocksize;

	dev = camdd_alloc_dev(CAMDD_DEV_FILE, NULL, 0, retry_count, timeout);
	if (dev == NULL)
		goto bailout;

	file_dev = &dev->dev_spec.file;
	file_dev->fd = fd;
	strlcpy(file_dev->filename, io_opts->dev_name,
	    sizeof(file_dev->filename));
	strlcpy(dev->device_name, io_opts->dev_name, sizeof(dev->device_name));
	if (blocksize == 0)
		dev->blocksize = CAMDD_FILE_DEFAULT_BLOCK;
	else
		dev->blocksize = blocksize;

	if ((io_opts->queue_depth != 0)
	 && (io_opts->queue_depth != 1)) {
		warnx("Queue depth %ju for %s ignored, only 1 outstanding "
		    "command supported", (uintmax_t)io_opts->queue_depth,
		    io_opts->dev_name);
	}
	dev->target_queue_depth = CAMDD_FILE_DEFAULT_DEPTH;
	dev->run = camdd_file_run;
	dev->fetch = NULL;

	/*
	 * We can effectively access files on byte boundaries.  We'll reset
	 * this for devices like disks that can be accessed on sector
	 * boundaries.
	 */
	dev->sector_size = 1;

	if ((fd != STDIN_FILENO)
	 && (fd != STDOUT_FILENO)) {
		int retval;

		retval = fstat(fd, &file_dev->sb);
		if (retval != 0) {
			warn("Cannot stat %s", dev->device_name);
			goto bailout_error;
		}
		if (S_ISREG(file_dev->sb.st_mode)) {
			file_dev->file_type = CAMDD_FILE_REG;
		} else if (S_ISCHR(file_dev->sb.st_mode)) {
			int type;

			if (ioctl(fd, FIODTYPE, &type) == -1)
				err(1, "FIODTYPE ioctl failed on %s",
				    dev->device_name);
			else {
				if (type & D_TAPE)
					file_dev->file_type = CAMDD_FILE_TAPE;
				else if (type & D_DISK)
					file_dev->file_type = CAMDD_FILE_DISK;
				else if (type & D_MEM)
					file_dev->file_type = CAMDD_FILE_MEM;
				else if (type & D_TTY)
					file_dev->file_type = CAMDD_FILE_TTY;
			}
		} else if (S_ISDIR(file_dev->sb.st_mode)) {
			errx(1, "cannot operate on directory %s",
			    dev->device_name);
		} else if (S_ISFIFO(file_dev->sb.st_mode)) {
			file_dev->file_type = CAMDD_FILE_PIPE;
		} else
			errx(1, "Cannot determine file type for %s",
			    dev->device_name);

		switch (file_dev->file_type) {
		case CAMDD_FILE_REG:
			if (file_dev->sb.st_size != 0)
				dev->max_sector = file_dev->sb.st_size - 1;
			else
				dev->max_sector = 0;
			file_dev->file_flags |= CAMDD_FF_CAN_SEEK;
			break;
		case CAMDD_FILE_TAPE: {
			uint64_t max_iosize, max_blk, min_blk, blk_gran;
			/*
			 * Check block limits and maximum effective iosize.
			 * Make sure the blocksize is within the block
			 * limits (and a multiple of the minimum blocksize)
			 * and that the blocksize is <= maximum effective
			 * iosize.
			 */
			retval = camdd_probe_tape(fd, dev->device_name,
			    &max_iosize, &max_blk, &min_blk, &blk_gran);
			if (retval != 0)
				errx(1, "Unable to probe tape %s",
				    dev->device_name);

			/*
			 * The blocksize needs to be <= the maximum
			 * effective I/O size of the tape device.  Note
			 * that this also takes into account the maximum
			 * blocksize reported by READ BLOCK LIMITS.
			 */
			if (dev->blocksize > max_iosize) {
				warnx("Blocksize %u too big for %s, limiting "
				    "to %ju", dev->blocksize, dev->device_name,
				    max_iosize);
				dev->blocksize = max_iosize;
			}

			/*
			 * The blocksize needs to be at least min_blk;
			 */
			if (dev->blocksize < min_blk) {
				warnx("Blocksize %u too small for %s, "
				    "increasing to %ju", dev->blocksize,
				    dev->device_name, min_blk);
				dev->blocksize = min_blk;
			}

			/*
			 * And the blocksize needs to be a multiple of
			 * the block granularity.
			 */
			if ((blk_gran != 0)
			 && (dev->blocksize % (1 << blk_gran))) {
				warnx("Blocksize %u for %s not a multiple of "
				    "%d, adjusting to %d", dev->blocksize,
				    dev->device_name, (1 << blk_gran),
				    dev->blocksize & ~((1 << blk_gran) - 1));
				dev->blocksize &= ~((1 << blk_gran) - 1);
			}

			if (dev->blocksize == 0) {
				errx(1, "Unable to derive valid blocksize for "
				    "%s", dev->device_name);
			}

			/*
			 * For tape drives, set the sector size to the
			 * blocksize so that we make sure not to write
			 * less than the blocksize out to the drive.
			 */
			dev->sector_size = dev->blocksize;
			break;
		}
		case CAMDD_FILE_DISK: {
			off_t media_size;
			unsigned int sector_size;

			file_dev->file_flags |= CAMDD_FF_CAN_SEEK;

			if (ioctl(fd, DIOCGSECTORSIZE, &sector_size) == -1) {
				err(1, "DIOCGSECTORSIZE ioctl failed on %s",
				    dev->device_name);
			}

			if (sector_size == 0) {
				errx(1, "DIOCGSECTORSIZE ioctl returned "
				    "invalid sector size %u for %s",
				    sector_size, dev->device_name);
			}

			if (ioctl(fd, DIOCGMEDIASIZE, &media_size) == -1) {
				err(1, "DIOCGMEDIASIZE ioctl failed on %s",
				    dev->device_name);
			}

			if (media_size == 0) {
				errx(1, "DIOCGMEDIASIZE ioctl returned "
				    "invalid media size %ju for %s",
				    (uintmax_t)media_size, dev->device_name);
			}

			if (dev->blocksize % sector_size) {
				errx(1, "%s blocksize %u not a multiple of "
				    "sector size %u", dev->device_name,
				    dev->blocksize, sector_size);
			}

			dev->sector_size = sector_size;
			dev->max_sector = (media_size / sector_size) - 1;
			break;
		}
		case CAMDD_FILE_MEM:
			file_dev->file_flags |= CAMDD_FF_CAN_SEEK;
			break;
		default:
			break;
		}
	}

	if ((io_opts->offset != 0)
	 && ((file_dev->file_flags & CAMDD_FF_CAN_SEEK) == 0)) {
		warnx("Offset %ju specified for %s, but we cannot seek on %s",
		    io_opts->offset, io_opts->dev_name, io_opts->dev_name);
		goto bailout_error;
	}
#if 0
	else if ((io_opts->offset != 0)
		&& ((io_opts->offset % dev->sector_size) != 0)) {
		warnx("Offset %ju for %s is not a multiple of the "
		      "sector size %u", io_opts->offset, 
		      io_opts->dev_name, dev->sector_size);
		goto bailout_error;
	} else {
		dev->start_offset_bytes = io_opts->offset;
	}
#endif

bailout:
	return (dev);

bailout_error:
	camdd_free_dev(dev);
	return (NULL);
}