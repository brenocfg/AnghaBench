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
typedef  char u8 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int RANDOM_ENTROPY_SIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int own_pool_ready ; 
 int /*<<< orphan*/  random_entropy_file ; 
 scalar_t__ random_get_bytes (char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void random_write_entropy(void)
{
	char buf[RANDOM_ENTROPY_SIZE];
	FILE *f;
	u8 opr;
	int fail = 0;

	if (!random_entropy_file)
		return;

	if (random_get_bytes(buf, RANDOM_ENTROPY_SIZE) < 0)
		return;

	f = fopen(random_entropy_file, "wb");
	if (f == NULL) {
		wpa_printf(MSG_ERROR, "random: Could not open entropy file %s "
			   "for writing", random_entropy_file);
		return;
	}

	opr = own_pool_ready > 0xff ? 0xff : own_pool_ready;
	if (fwrite(&opr, 1, 1, f) != 1 ||
	    fwrite(buf, RANDOM_ENTROPY_SIZE, 1, f) != 1)
		fail = 1;
	fclose(f);
	if (fail) {
		wpa_printf(MSG_ERROR, "random: Could not write entropy data "
			   "to %s", random_entropy_file);
		return;
	}

	wpa_printf(MSG_DEBUG, "random: Updated entropy file %s "
		   "(own_pool_ready=%u)",
		   random_entropy_file, own_pool_ready);
}