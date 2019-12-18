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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct dnssl_addr {int /*<<< orphan*/  da_dom; } ;
struct dnssl {int /*<<< orphan*/  dn_ltime; } ;
typedef  int /*<<< orphan*/  hbuf ;

/* Variables and functions */
 int NI_MAXHOST ; 
 int SSBUFLEN ; 
 int /*<<< orphan*/  dname_labeldec (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* sec2str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
action_show_dnssl(void *msg)
{
	struct dnssl *dns;
	struct dnssl_addr *dna;
	uint16_t *dns_cnt;
	uint16_t *dna_cnt;
	int i;
	int j;
	char *p;
	uint32_t ltime;
	char hbuf[NI_MAXHOST];
	char ssbuf[SSBUFLEN];

	p = msg;
	dns_cnt = (uint16_t *)p;
	p += sizeof(*dns_cnt);

	if (*dns_cnt > 0) {
		for (i = 0; i < *dns_cnt; i++) {
			dns = (struct dnssl *)p;
			ltime = dns->dn_ltime;
			p += sizeof(*dns);

			dna_cnt = (uint16_t *)p;
			p += sizeof(*dna_cnt);
			if (*dna_cnt > 0)
				for (j = 0; j < *dna_cnt; j++) {
					dna = (struct dnssl_addr *)p;
					dname_labeldec(hbuf, sizeof(hbuf),
					    dna->da_dom);
					printf("\t  %s (ltime=%s)\n",
					    hbuf, sec2str(ltime, ssbuf));
					p += sizeof(*dna);
				}
		}
	}

	return (0);
}