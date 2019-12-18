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
typedef  int /*<<< orphan*/  yn ;
struct TYPE_3__ {int fi_flx; int /*<<< orphan*/  fi_dst; int /*<<< orphan*/  fi_src; } ;
struct TYPE_4__ {int* fin_data; int fin_id; TYPE_1__ fin_fi; scalar_t__ fin_out; } ;
struct frauth {int fra_pass; int fra_index; TYPE_2__ fra_info; int /*<<< orphan*/ * fra_buf; scalar_t__ fra_len; } ;
typedef  TYPE_1__ fr_ip_t ;
typedef  TYPE_2__ fr_info_t ;

/* Variables and functions */
 int FI_TCPUDP ; 
 int FR_BLOCK ; 
 int FR_INQUE ; 
 int FR_KEEPSTATE ; 
 int FR_NOMATCH ; 
 int FR_OUTQUE ; 
 int FR_PASS ; 
 int /*<<< orphan*/  IPL_NAME ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIOCAUTHR ; 
 int /*<<< orphan*/  SIOCAUTHW ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct frauth**) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

main()
{
	struct frauth fra;
	struct frauth *frap = &fra;
	fr_info_t *fin = &fra.fra_info;
	fr_ip_t	*fi = &fin->fin_fi;
	char yn[16];
	int fd;

	fd = open(IPL_NAME, O_RDWR);
	fra.fra_len = 0;
	fra.fra_buf = NULL;
	while (ioctl(fd, SIOCAUTHW, &frap) == 0) {
		if (fra.fra_info.fin_out)
			fra.fra_pass = FR_OUTQUE;
		else
			fra.fra_pass = FR_INQUE;

		printf("%s ", inet_ntoa(fi->fi_src));
		if (fi->fi_flx & FI_TCPUDP)
			printf("port %d ", fin->fin_data[0]);
		printf("-> %s ", inet_ntoa(fi->fi_dst));
		if (fi->fi_flx & FI_TCPUDP)
			printf("port %d ", fin->fin_data[1]);
		printf("\n");
		printf("Allow packet through ? [y/n]");
		fflush(stdout);
		if (!fgets(yn, sizeof(yn), stdin))
			break;
		fflush(stdin);
		if (yn[0] == 'n' || yn[0] == 'N')
			fra.fra_pass |= FR_BLOCK;
		else if (yn[0] == 'y' || yn[0] == 'Y') {
			fra.fra_pass |= FR_PASS;
			if (fra.fra_info.fin_fi.fi_flx & FI_TCPUDP)
				fra.fra_pass |= FR_KEEPSTATE;
		} else
			fra.fra_pass |= FR_NOMATCH;
		printf("answer = %c (%x), id %d idx %d\n", yn[0],
			fra.fra_pass, fra.fra_info.fin_id, fra.fra_index);
		if (ioctl(fd, SIOCAUTHR, &frap) != 0)
			perror("SIOCAUTHR");
	}
	fprintf(stderr, "errno=%d \n", errno);
	perror("frauth-SIOCAUTHW");
}