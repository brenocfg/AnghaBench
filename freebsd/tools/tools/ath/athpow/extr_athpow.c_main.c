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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_int ;
struct ath_diag {char* ad_name; int ad_out_size; void* ad_out_data; int /*<<< orphan*/  ad_id; } ;
typedef  int /*<<< orphan*/  revs ;
typedef  int /*<<< orphan*/  ratesArray ;
typedef  int /*<<< orphan*/  pcdacTable ;
typedef  void* caddr_t ;
typedef  int /*<<< orphan*/  HAL_REVS ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  HAL_DIAG_PCDAC ; 
 int /*<<< orphan*/  HAL_DIAG_REVS ; 
 int /*<<< orphan*/  HAL_DIAG_TXRATES ; 
 scalar_t__ IS_2413 (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_5413 (int /*<<< orphan*/ *) ; 
 int MAX (int,int) ; 
 int PWR_TABLE_SIZE ; 
 int PWR_TABLE_SIZE_2413 ; 
 int /*<<< orphan*/  SIOCGATHDIAG ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ath_diag*) ; 
 char* optarg ; 
 int /*<<< orphan*/  printPcdacTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printPowerPerRate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printRevs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	int s, i, verbose = 0, c;
	struct ath_diag atd;
	const char *ifname;
	HAL_REVS revs;
	u_int16_t pcdacTable[MAX(PWR_TABLE_SIZE,PWR_TABLE_SIZE_2413)];
	u_int16_t ratesArray[37];
	u_int nrates, npcdac;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		err(1, "socket");
	ifname = getenv("ATH");
	if (!ifname)
		ifname = ATH_DEFAULT;
	while ((c = getopt(argc, argv, "i:v")) != -1)
		switch (c) {
		case 'i':
			ifname = optarg;
			break;
		case 'v':
			verbose++;
			break;
		default:
			usage(argv[0]);
		}
	strncpy(atd.ad_name, ifname, sizeof (atd.ad_name));

	atd.ad_id = HAL_DIAG_REVS;
	atd.ad_out_data = (caddr_t) &revs;
	atd.ad_out_size = sizeof(revs);
	if (ioctl(s, SIOCGATHDIAG, &atd) < 0)
		err(1, atd.ad_name);

	if (verbose)
		printRevs(stdout, &revs);

	atd.ad_id = HAL_DIAG_TXRATES;
	atd.ad_out_data = (caddr_t) ratesArray;
	atd.ad_out_size = sizeof(ratesArray);
	if (ioctl(s, SIOCGATHDIAG, &atd) < 0)
		err(1, atd.ad_name);
	nrates = sizeof(ratesArray) / sizeof(u_int16_t);

	atd.ad_id = HAL_DIAG_PCDAC;
	atd.ad_out_data = (caddr_t) pcdacTable;
	atd.ad_out_size = sizeof(pcdacTable);
	if (ioctl(s, SIOCGATHDIAG, &atd) < 0)
		err(1, atd.ad_name);
	if (IS_2413(&revs) || IS_5413(&revs))
		npcdac = PWR_TABLE_SIZE_2413;
	else
		npcdac = PWR_TABLE_SIZE;

	printf("PCDAC table:\n");
	printPcdacTable(stdout, pcdacTable, npcdac);

	printf("Power per rate table:\n");
	printPowerPerRate(stdout, ratesArray, nrates);

	return 0;
}