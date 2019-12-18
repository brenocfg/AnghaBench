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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct fis_image_desc {int* name; scalar_t__ offset; scalar_t__ size; struct fis_image_desc* next; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  FISDIR_NAME ; 
 int /*<<< orphan*/  REDBCFG_NAME ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  g_redboot_print (int,struct fis_image_desc*) ; 
 scalar_t__ match (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ nameok (int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static struct fis_image_desc *
parse_fis_directory(u_char *buf, size_t bufsize, off_t offset, uint32_t offmask)
{
#define	match(a,b)	(bcmp(a, b, sizeof(b)-1) == 0)
	struct fis_image_desc *fd, *efd;
	struct fis_image_desc *fisdir, *redbcfg;
	struct fis_image_desc *head, **tail;
	int i;

	fd = (struct fis_image_desc *)buf;
	efd = fd + (bufsize / sizeof(struct fis_image_desc));
#if 0
	/*
	 * Find the start of the FIS table.
	 */
	while (fd < efd && fd->name[0] != 0xff)
		fd++;
	if (fd == efd)
		return (NULL);
	if (bootverbose)
		printf("RedBoot FIS table starts at 0x%jx\n",
		    offset + fd - (struct fis_image_desc *) buf);
#endif
	/*
	 * Scan forward collecting entries in a list.
	 */
	fisdir = redbcfg = NULL;
	*(tail = &head) = NULL;
	for (i = 0; fd < efd; i++, fd++) {
		if (fd->name[0] == 0xff)
			continue;
		if (match(fd->name, FISDIR_NAME))
			fisdir = fd;
		else if (match(fd->name, REDBCFG_NAME))
			redbcfg = fd;
		if (nameok(fd->name)) {
			/*
			 * NB: flash address includes platform mapping;
			 *     strip it so we have only a flash offset.
			 */
			fd->offset &= offmask;
			if (bootverbose)
				g_redboot_print(i, fd);
			*tail = fd;
			*(tail = &fd->next) = NULL;
		}
	}
	if (fisdir == NULL) {
		if (bootverbose)
			printf("No RedBoot FIS table located at %lu\n",
			    (long) offset);
		return (NULL);
	}
	if (redbcfg != NULL &&
	    fisdir->offset + fisdir->size == redbcfg->offset) {
		/*
		 * Merged FIS/RedBoot config directory.
		 */
		if (bootverbose)
			printf("FIS/RedBoot merged at 0x%jx (not yet)\n",
			    offset + fisdir->offset);
		/* XXX */
	}
	return head;
#undef match
}