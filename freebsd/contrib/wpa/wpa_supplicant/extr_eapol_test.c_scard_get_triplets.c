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
struct scard_data {int dummy; } ;
struct eapol_test_data {int /*<<< orphan*/  pcsc_reader; } ;
typedef  int /*<<< orphan*/  imsi ;
typedef  int /*<<< orphan*/  _rand ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  os_memset (unsigned char*,int,int) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  scard_deinit (struct scard_data*) ; 
 scalar_t__ scard_get_imsi (struct scard_data*,char*,size_t*) ; 
 scalar_t__ scard_gsm_auth (struct scard_data*,unsigned char*,unsigned char*,unsigned char*) ; 
 struct scard_data* scard_init (int /*<<< orphan*/ ) ; 
 scalar_t__ scard_set_pin (struct scard_data*,char*) ; 
 int wpa_debug_level ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int scard_get_triplets(struct eapol_test_data *e, int argc, char *argv[])
{
	struct scard_data *scard;
	size_t len;
	char imsi[20];
	unsigned char _rand[16];
	unsigned char sres[4];
	unsigned char kc[8];
	int num_triplets;
	int i;
	size_t j;

	if (argc < 2 || ((num_triplets = atoi(argv[1])) <= 0)) {
		printf("invalid parameters for sim command\n");
		return -1;
	}

	if (argc <= 2 || os_strcmp(argv[2], "debug") != 0) {
		/* disable debug output */
		wpa_debug_level = 99;
	}

	scard = scard_init(e->pcsc_reader);
	if (scard == NULL) {
		printf("Failed to open smartcard connection\n");
		return -1;
	}
	if (scard_set_pin(scard, argv[0])) {
		wpa_printf(MSG_WARNING, "PIN validation failed");
		scard_deinit(scard);
		return -1;
	}

	len = sizeof(imsi);
	if (scard_get_imsi(scard, imsi, &len)) {
		scard_deinit(scard);
		return -1;
	}

	for (i = 0; i < num_triplets; i++) {
		os_memset(_rand, i, sizeof(_rand));
		if (scard_gsm_auth(scard, _rand, sres, kc))
			break;

		/* IMSI:Kc:SRES:RAND */
		for (j = 0; j < len; j++)
			printf("%c", imsi[j]);
		printf(":");
		for (j = 0; j < 8; j++)
			printf("%02X", kc[j]);
		printf(":");
		for (j = 0; j < 4; j++)
			printf("%02X", sres[j]);
		printf(":");
		for (j = 0; j < 16; j++)
			printf("%02X", _rand[j]);
		printf("\n");
	}

	scard_deinit(scard);

	return 0;
}