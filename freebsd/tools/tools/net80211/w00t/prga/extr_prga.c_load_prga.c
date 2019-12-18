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
struct params {char* fname; int prga_len; int /*<<< orphan*/  prga; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 

void load_prga(struct params *p)
{
	int fd;
	int rd;

	fd = open(p->fname, O_RDONLY);
	if (fd == -1) {
		p->prga_len = 0;
		return;
	}

	rd = read(fd, p->iv, 3);
	if (rd == -1)
		err(1, "read()");
	if (rd != 3) {
		printf("Short read\n");
		exit(1);
	}

	rd = read(fd, p->prga, sizeof(p->prga));
	if (rd == -1)
		err(1, "read()");
	p->prga_len = rd;
	
	printf("Loaded %d PRGA from %s\n", p->prga_len, p->fname);
	close(fd);
}