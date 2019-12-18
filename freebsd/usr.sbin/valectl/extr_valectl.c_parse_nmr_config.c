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
struct nmreq {int nr_tx_rings; int nr_rx_rings; int nr_tx_slots; int nr_rx_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,...) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
parse_nmr_config(const char* conf, struct nmreq *nmr)
{
	char *w, *tok;
	int i, v;

	nmr->nr_tx_rings = nmr->nr_rx_rings = 0;
	nmr->nr_tx_slots = nmr->nr_rx_slots = 0;
	if (conf == NULL || ! *conf)
		return;
	w = strdup(conf);
	for (i = 0, tok = strtok(w, ","); tok; i++, tok = strtok(NULL, ",")) {
		v = atoi(tok);
		switch (i) {
		case 0:
			nmr->nr_tx_slots = nmr->nr_rx_slots = v;
			break;
		case 1:
			nmr->nr_rx_slots = v;
			break;
		case 2:
			nmr->nr_tx_rings = nmr->nr_rx_rings = v;
			break;
		case 3:
			nmr->nr_rx_rings = v;
			break;
		default:
			D("ignored config: %s", tok);
			break;
		}
	}
	D("txr %d txd %d rxr %d rxd %d",
			nmr->nr_tx_rings, nmr->nr_tx_slots,
			nmr->nr_rx_rings, nmr->nr_rx_slots);
	free(w);
}