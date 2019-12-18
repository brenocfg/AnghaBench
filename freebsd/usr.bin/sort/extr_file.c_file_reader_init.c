#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {size_t st_size; } ;
struct file_reader {char elsymb; int fd; size_t mmapsize; int cbsz; scalar_t__ bsz; int /*<<< orphan*/ * file; void* buffer; scalar_t__ strbeg; int /*<<< orphan*/ * mmapaddr; int /*<<< orphan*/ * mmapptr; int /*<<< orphan*/  fname; } ;
struct TYPE_2__ {scalar_t__ zflag; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int MAP_NOCORE ; 
 int MAP_NOSYNC ; 
 int MAP_PREFAULT_READ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int READ_CHUNK ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * compress_program ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fread (void*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  memset (struct file_reader*,int /*<<< orphan*/ ,int) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * openfile (char const*,char*) ; 
 void* sort_malloc (int) ; 
 TYPE_1__ sort_opts_vals ; 
 int /*<<< orphan*/  sort_strdup (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ use_mmap ; 

struct file_reader *
file_reader_init(const char *fsrc)
{
	struct file_reader *ret;

	if (fsrc == NULL)
		fsrc = "-";

	ret = sort_malloc(sizeof(struct file_reader));
	memset(ret, 0, sizeof(struct file_reader));

	ret->elsymb = '\n';
	if (sort_opts_vals.zflag)
		ret->elsymb = 0;

	ret->fname = sort_strdup(fsrc);

	if (strcmp(fsrc, "-") && (compress_program == NULL) && use_mmap) {

		do {
			struct stat stat_buf;
			void *addr;
			size_t sz = 0;
			int fd, flags;

			flags = MAP_NOCORE | MAP_NOSYNC;

			fd = open(fsrc, O_RDONLY);
			if (fd < 0)
				err(2, NULL);

			if (fstat(fd, &stat_buf) < 0) {
				close(fd);
				break;
			}

			sz = stat_buf.st_size;

#if defined(MAP_PREFAULT_READ)
			flags |= MAP_PREFAULT_READ;
#endif

			addr = mmap(NULL, sz, PROT_READ, flags, fd, 0);
			if (addr == MAP_FAILED) {
				close(fd);
				break;
			}

			ret->fd = fd;
			ret->mmapaddr = addr;
			ret->mmapsize = sz;
			ret->mmapptr = ret->mmapaddr;

		} while (0);
	}

	if (ret->mmapaddr == NULL) {
		ret->file = openfile(fsrc, "r");
		if (ret->file == NULL)
			err(2, NULL);

		if (strcmp(fsrc, "-")) {
			ret->cbsz = READ_CHUNK;
			ret->buffer = sort_malloc(ret->cbsz);
			ret->bsz = 0;
			ret->strbeg = 0;

			ret->bsz = fread(ret->buffer, 1, ret->cbsz, ret->file);
			if (ret->bsz == 0) {
				if (ferror(ret->file))
					err(2, NULL);
			}
		}
	}

	return (ret);
}