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
typedef  int u8 ;
struct milenage_parameters {int /*<<< orphan*/  sqn; int /*<<< orphan*/  ki; int /*<<< orphan*/  opc; } ;

/* Variables and functions */
 int EAP_AKA_AUTS_LEN ; 
 int EAP_AKA_RAND_LEN ; 
 int /*<<< orphan*/  db_update_milenage_sqn (struct milenage_parameters*) ; 
 struct milenage_parameters* get_milenage (char*) ; 
 scalar_t__ hexstr2bin (char*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ milenage_auts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sqn_changes ; 
 scalar_t__ stdout_debug ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int aka_auts(char *imsi, char *resp, size_t resp_len)
{
	char *auts, *__rand;
	u8 _auts[EAP_AKA_AUTS_LEN], _rand[EAP_AKA_RAND_LEN], sqn[6];
	struct milenage_parameters *m;

	resp[0] = '\0';

	/* AKA-AUTS <IMSI> <AUTS> <RAND> */

	auts = strchr(imsi, ' ');
	if (auts == NULL)
		return -1;
	*auts++ = '\0';

	__rand = strchr(auts, ' ');
	if (__rand == NULL)
		return -1;
	*__rand++ = '\0';

	if (stdout_debug) {
		printf("AKA-AUTS: IMSI=%s AUTS=%s RAND=%s\n",
		       imsi, auts, __rand);
	}
	if (hexstr2bin(auts, _auts, EAP_AKA_AUTS_LEN) ||
	    hexstr2bin(__rand, _rand, EAP_AKA_RAND_LEN)) {
		printf("Could not parse AUTS/RAND\n");
		return -1;
	}

	m = get_milenage(imsi);
	if (m == NULL) {
		printf("Unknown IMSI: %s\n", imsi);
		return -1;
	}

	if (milenage_auts(m->opc, m->ki, _rand, _auts, sqn)) {
		printf("AKA-AUTS: Incorrect MAC-S\n");
	} else {
		memcpy(m->sqn, sqn, 6);
		if (stdout_debug) {
			printf("AKA-AUTS: Re-synchronized: "
			       "SQN=%02x%02x%02x%02x%02x%02x\n",
			       sqn[0], sqn[1], sqn[2], sqn[3], sqn[4], sqn[5]);
		}
#ifdef CONFIG_SQLITE
		db_update_milenage_sqn(m);
#endif /* CONFIG_SQLITE */
		sqn_changes = 1;
	}

	return 0;
}