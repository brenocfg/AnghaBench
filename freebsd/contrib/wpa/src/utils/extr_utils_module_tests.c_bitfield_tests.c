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
struct bitfield {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct bitfield* bitfield_alloc (int) ; 
 int /*<<< orphan*/  bitfield_clear (struct bitfield*,int) ; 
 int /*<<< orphan*/  bitfield_free (struct bitfield*) ; 
 int bitfield_get_first_zero (struct bitfield*) ; 
 scalar_t__ bitfield_is_set (struct bitfield*,int) ; 
 int /*<<< orphan*/  bitfield_set (struct bitfield*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int bitfield_tests(void)
{
	struct bitfield *bf;
	int i;
	int errors = 0;

	wpa_printf(MSG_INFO, "bitfield tests");

	bf = bitfield_alloc(123);
	if (bf == NULL)
		return -1;

	for (i = 0; i < 123; i++) {
		if (bitfield_is_set(bf, i) || bitfield_is_set(bf, i + 1))
			errors++;
		if (i > 0 && bitfield_is_set(bf, i - 1))
			errors++;
		bitfield_set(bf, i);
		if (!bitfield_is_set(bf, i))
			errors++;
		bitfield_clear(bf, i);
		if (bitfield_is_set(bf, i))
			errors++;
	}

	for (i = 123; i < 200; i++) {
		if (bitfield_is_set(bf, i) || bitfield_is_set(bf, i + 1))
			errors++;
		if (i > 0 && bitfield_is_set(bf, i - 1))
			errors++;
		bitfield_set(bf, i);
		if (bitfield_is_set(bf, i))
			errors++;
		bitfield_clear(bf, i);
		if (bitfield_is_set(bf, i))
			errors++;
	}

	for (i = 0; i < 123; i++) {
		if (bitfield_is_set(bf, i) || bitfield_is_set(bf, i + 1))
			errors++;
		bitfield_set(bf, i);
		if (!bitfield_is_set(bf, i))
			errors++;
	}

	for (i = 0; i < 123; i++) {
		if (!bitfield_is_set(bf, i))
			errors++;
		bitfield_clear(bf, i);
		if (bitfield_is_set(bf, i))
			errors++;
	}

	for (i = 0; i < 123; i++) {
		if (bitfield_get_first_zero(bf) != i)
			errors++;
		bitfield_set(bf, i);
	}
	if (bitfield_get_first_zero(bf) != -1)
		errors++;
	for (i = 0; i < 123; i++) {
		if (!bitfield_is_set(bf, i))
			errors++;
		bitfield_clear(bf, i);
		if (bitfield_get_first_zero(bf) != i)
			errors++;
		bitfield_set(bf, i);
	}
	if (bitfield_get_first_zero(bf) != -1)
		errors++;

	bitfield_free(bf);

	bf = bitfield_alloc(8);
	if (bf == NULL)
		return -1;
	if (bitfield_get_first_zero(bf) != 0)
		errors++;
	for (i = 0; i < 8; i++)
		bitfield_set(bf, i);
	if (bitfield_get_first_zero(bf) != -1)
		errors++;
	bitfield_free(bf);

	if (errors) {
		wpa_printf(MSG_ERROR, "%d bitfield test(s) failed", errors);
		return -1;
	}

	return 0;
}