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
typedef  scalar_t__ uint8_t ;
typedef  char const* ldns_status ;
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (scalar_t__*) ; 
 char const* LDNS_STATUS_OK ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* ldns_pkt2wire (scalar_t__**,int /*<<< orphan*/  const*,size_t*) ; 

void
dump_hex(const ldns_pkt *pkt, const char *filename)
{
	uint8_t *wire = NULL;
	size_t size, i;
	FILE *fp;
	ldns_status status;
	
	fp = fopen(filename, "w");
	
	if (fp == NULL) {
		error("Unable to open %s for writing", filename);
		return;
	}
	
	status = ldns_pkt2wire(&wire, pkt, &size);
	
	if (status != LDNS_STATUS_OK) {
		error("Unable to convert packet: error code %u", status);
		LDNS_FREE(wire);
		fclose(fp);
		return;
	}
	
	fprintf(fp, "; 0");
	for (i = 1; i < 20; i++) {
		fprintf(fp, " %2u", (unsigned int) i);
	}
	fprintf(fp, "\n");
	fprintf(fp, ";--");
	for (i = 1; i < 20; i++) {
		fprintf(fp, " --");
	}
	fprintf(fp, "\n");
	for (i = 0; i < size; i++) {
		if (i % 20 == 0 && i > 0) {
			fprintf(fp, "\t;\t%4u-%4u\n", (unsigned int) i-19, (unsigned int) i);
		}
		fprintf(fp, " %02x", (unsigned int)wire[i]);
	}
	fprintf(fp, "\n");
	fclose(fp);
	LDNS_FREE(wire);
}