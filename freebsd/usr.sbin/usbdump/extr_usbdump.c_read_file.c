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
typedef  int uint8_t ;
struct usbcap {int /*<<< orphan*/  rfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fix_packets (int*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int le32toh (int) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  print_packets (int*,int) ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int uf_minor ; 

__attribute__((used)) static void
read_file(struct usbcap *p)
{
	int datalen;
	int ret;
	uint8_t *data;

	while ((ret = read(p->rfd, &datalen, sizeof(int))) == sizeof(int)) {
		datalen = le32toh(datalen);
		data = malloc(datalen);
		if (data == NULL)
			errx(EX_SOFTWARE, "Out of memory.");
		ret = read(p->rfd, data, datalen);
		if (ret != datalen) {
			err(EXIT_FAILURE, "Could not read complete "
			    "USB data payload");
		}
		if (uf_minor == 2)
			fix_packets(data, datalen);

		print_packets(data, datalen);
		free(data);
	}
}