#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pack_header {int dummy; } ;
struct hashfile {int dummy; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_5__ {scalar_t__ pack_size; int /*<<< orphan*/  pack_name; } ;
struct TYPE_4__ {scalar_t__ rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,double) ; 
 int git_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite (struct hashfile*,unsigned char*,int) ; 
 int /*<<< orphan*/  is_pack_valid (TYPE_2__*) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progress_state ; 
 TYPE_2__* reuse_packfile ; 
 double reuse_packfile_objects ; 
 scalar_t__ reuse_packfile_offset ; 
 TYPE_1__* the_hash_algo ; 
 double written ; 
 int xread (int,unsigned char*,int) ; 

__attribute__((used)) static off_t write_reused_pack(struct hashfile *f)
{
	unsigned char buffer[8192];
	off_t to_write, total;
	int fd;

	if (!is_pack_valid(reuse_packfile))
		die(_("packfile is invalid: %s"), reuse_packfile->pack_name);

	fd = git_open(reuse_packfile->pack_name);
	if (fd < 0)
		die_errno(_("unable to open packfile for reuse: %s"),
			  reuse_packfile->pack_name);

	if (lseek(fd, sizeof(struct pack_header), SEEK_SET) == -1)
		die_errno(_("unable to seek in reused packfile"));

	if (reuse_packfile_offset < 0)
		reuse_packfile_offset = reuse_packfile->pack_size - the_hash_algo->rawsz;

	total = to_write = reuse_packfile_offset - sizeof(struct pack_header);

	while (to_write) {
		int read_pack = xread(fd, buffer, sizeof(buffer));

		if (read_pack <= 0)
			die_errno(_("unable to read from reused packfile"));

		if (read_pack > to_write)
			read_pack = to_write;

		hashwrite(f, buffer, read_pack);
		to_write -= read_pack;

		/*
		 * We don't know the actual number of objects written,
		 * only how many bytes written, how many bytes total, and
		 * how many objects total. So we can fake it by pretending all
		 * objects we are writing are the same size. This gives us a
		 * smooth progress meter, and at the end it matches the true
		 * answer.
		 */
		written = reuse_packfile_objects *
				(((double)(total - to_write)) / total);
		display_progress(progress_state, written);
	}

	close(fd);
	written = reuse_packfile_objects;
	display_progress(progress_state, written);
	return reuse_packfile_offset - sizeof(struct pack_header);
}