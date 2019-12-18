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
struct params {int prga_len; int /*<<< orphan*/  prga; int /*<<< orphan*/  iv; int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

void save_prga(struct params *p)
{
	int fd;
	int rd;

	fd = open(p->fname, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		err(1, "open()");

	rd = write(fd, p->iv, 3);
	if (rd == -1)
		err(1, "write()");
	if (rd != 3) {
		printf("Short write\n");
		exit(1);
	}

	rd = write(fd, p->prga, p->prga_len);
	if (rd == -1)
		err(1, "write()");
	if (rd != p->prga_len) {
		printf("Wrote %d/%d\n", rd, p->prga_len);
		exit(1);
	}
	close(fd);

	printf("Got %d bytes of PRGA\n", p->prga_len);
}