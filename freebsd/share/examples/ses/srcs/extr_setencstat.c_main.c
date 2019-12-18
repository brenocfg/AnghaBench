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
typedef  scalar_t__ encioc_enc_status_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENCIOC_SETENCSTAT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(int a, char **v)
{
	int fd;
	long val;
	encioc_enc_status_t stat;

	if (a != 3) {
		fprintf(stderr, "usage: %s device enclosure_status\n", *v);
		return (1);
	}
	fd = open(v[1], O_RDWR);
	if (fd < 0) {
		perror(v[1]);
		return (1);
	}
	
	val =  strtol(v[2], NULL, 0);
	stat = (encioc_enc_status_t)val;
	if (ioctl(fd, ENCIOC_SETENCSTAT, (caddr_t) &stat) < 0) {
		perror("ENCIOC_SETENCSTAT");
	}
	(void) close(fd);
	return (0);
}