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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MBRSIZE ; 
 int OFF_MAGIC ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int boot0bs (int /*<<< orphan*/ *) ; 
 int boot0version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int cv2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
read_mbr(const char *disk, u_int8_t **mbr, int check_version)
{
    u_int8_t buf[MBRSIZE];
    int mbr_size, fd;
    int ver;
    ssize_t n;

    if ((fd = open(disk, O_RDONLY)) == -1)
        err(1, "open %s", disk);
    if ((n = read(fd, buf, MBRSIZE)) == -1)
        err(1, "read %s", disk);
    if (n != MBRSIZE)
        errx(1, "%s: short read", disk);
    if (cv2(buf + OFF_MAGIC) != 0xaa55)
        errx(1, "%s: bad magic", disk);

    if (! (ver = boot0bs(buf))) {
	if (check_version)
	    errx(1, "%s: unknown or incompatible boot code", disk);
    } else if (boot0version(buf) == 0x101) {
	mbr_size = 1024;
	if ((*mbr = malloc(mbr_size)) == NULL)
	    errx(1, "%s: unable to allocate read buffer", disk);
	if (lseek(fd, 0, SEEK_SET) == -1 ||
	    (n = read(fd, *mbr, mbr_size)) == -1)
	    err(1, "%s", disk);
	if (n != mbr_size)
	    errx(1, "%s: short read", disk);
	close(fd);
	return (mbr_size);
    }
    if ((*mbr = malloc(sizeof(buf))) == NULL)
	errx(1, "%s: unable to allocate MBR buffer", disk);
    memcpy(*mbr, buf, sizeof(buf));
    close(fd);

    return sizeof(buf);
}