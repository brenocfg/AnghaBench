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
typedef  int /*<<< orphan*/  bitstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int _bit_byte (int) ; 
 int /*<<< orphan*/  _bit_mask (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bit_alloc (int const) ; 
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bit_nclear (int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  bit_nset (int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bit_test (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bitstr_size (int) ; 
 int /*<<< orphan*/  clearbits (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printbits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static void
calculate_data(FILE *file, const int test_length)
{
	int i;
	bitstr_t *bs;

	assert(test_length >= 4);

	(void) fprintf(file, "Testing with TEST_LENGTH = %d\n\n", test_length);

	(void) fprintf(file, "test _bit_byte, _bit_mask, and bitstr_size\n");
	(void) fprintf(file, "  i   _bit_byte(i)   _bit_mask(i) bitstr_size(i)\n");

	for (i=0; i < test_length; i++) {
		(void) fprintf(file, "%3d%15u%15u%15zu\n",
			i, _bit_byte(i), _bit_mask(i), bitstr_size(i));
	}

	bs = bit_alloc(test_length);
	clearbits(bs, test_length);
	(void) fprintf(file, "\ntest bit_alloc, clearbits, bit_ffc, bit_ffs\n");
	(void) fprintf(file, "be:   0  -1 ");
	for (i=0; i < test_length; i++)
		(void) fprintf(file, "%c", '0');
	(void) fprintf(file, "\nis: ");
	printbits(file, bs, test_length);

	(void) fprintf(file, "\ntest bit_set\n");
	for (i=0; i < test_length; i+=3)
		bit_set(bs, i);
	(void) fprintf(file, "be:   1   0 ");
	for (i=0; i < test_length; i++)
		(void) fprintf(file, "%c", "100"[i % 3]);
	(void) fprintf(file, "\nis: ");
	printbits(file, bs, test_length);

	(void) fprintf(file, "\ntest bit_clear\n");
	for (i=0; i < test_length; i+=6)
		bit_clear(bs, i);
	(void) fprintf(file, "be:   0   3 ");
	for (i=0; i < test_length; i++)
		(void) fprintf(file, "%c", "000100"[i % 6]);
	(void) fprintf(file, "\nis: ");
	printbits(file, bs, test_length);

	(void) fprintf(file, "\ntest bit_test using previous bitstring\n");
	(void) fprintf(file, "  i    bit_test(i)\n");
	for (i=0; i < test_length; i++)
		(void) fprintf(file, "%3d%15d\n", i, bit_test(bs, i));

	clearbits(bs, test_length);
	(void) fprintf(file, "\ntest clearbits\n");
	(void) fprintf(file, "be:   0  -1 ");
	for (i=0; i < test_length; i++)
		(void) fprintf(file, "%c", '0');
	(void) fprintf(file, "\nis: ");
	printbits(file, bs, test_length);

	(void) fprintf(file, "\ntest bit_nset and bit_nclear\n");
	bit_nset(bs, 1, test_length - 2);
	(void) fprintf(file, "be:   0   1 0");
	for (i=0; i < test_length - 2; i++)
		(void) fprintf(file, "%c", '1');
	(void) fprintf(file, "0\nis: ");
	printbits(file, bs, test_length);

	bit_nclear(bs, 2, test_length - 3);
	(void) fprintf(file, "be:   0   1 01");
	for (i=0; i < test_length - 4; i++)
		(void) fprintf(file, "%c", '0');
	(void) fprintf(file, "10\nis: ");
	printbits(file, bs, test_length);

	bit_nclear(bs, 0, test_length - 1);
	(void) fprintf(file, "be:   0  -1 ");
	for (i=0; i < test_length; i++)
		(void) fprintf(file, "%c", '0');
	(void) fprintf(file, "\nis: ");
	printbits(file, bs, test_length);
	bit_nset(bs, 0, test_length - 2);
	(void) fprintf(file, "be: %3d   0 ",test_length - 1);
	for (i=0; i < test_length - 1; i++)
		(void) fprintf(file, "%c", '1');
	fprintf(file, "%c", '0');
	(void) fprintf(file, "\nis: ");
	printbits(file, bs, test_length);
	bit_nclear(bs, 0, test_length - 1);
	(void) fprintf(file, "be:   0  -1 ");
	for (i=0; i < test_length; i++)
		(void) fprintf(file, "%c", '0');
	(void) fprintf(file, "\nis: ");
	printbits(file, bs, test_length);

	(void) fprintf(file, "\n");
	(void) fprintf(file, "first 1 bit should move right 1 position each line\n");
	for (i=0; i < test_length; i++) {
		bit_nclear(bs, 0, test_length - 1);
		bit_nset(bs, i, test_length - 1);
		(void) fprintf(file, "%3d ", i); printbits(file, bs, test_length);
	}

	(void) fprintf(file, "\n");
	(void) fprintf(file, "first 0 bit should move right 1 position each line\n");
	for (i=0; i < test_length; i++) {
		bit_nset(bs, 0, test_length - 1);
		bit_nclear(bs, i, test_length - 1);
		(void) fprintf(file, "%3d ", i); printbits(file, bs, test_length);
	}

	(void) fprintf(file, "\n");
	(void) fprintf(file, "first 0 bit should move left 1 position each line\n");
	for (i=0; i < test_length; i++) {
		bit_nclear(bs, 0, test_length - 1);
		bit_nset(bs, 0, test_length - 1 - i);
		(void) fprintf(file, "%3d ", i); printbits(file, bs, test_length);
	}

	(void) fprintf(file, "\n");
	(void) fprintf(file, "first 1 bit should move left 1 position each line\n");
	for (i=0; i < test_length; i++) {
		bit_nset(bs, 0, test_length - 1);
		bit_nclear(bs, 0, test_length - 1 - i);
		(void) fprintf(file, "%3d ", i); printbits(file, bs, test_length);
	}

	(void) fprintf(file, "\n");
	(void) fprintf(file, "0 bit should move right 1 position each line\n");
	for (i=0; i < test_length; i++) {
		bit_nset(bs, 0, test_length - 1);
		bit_nclear(bs, i, i);
		(void) fprintf(file, "%3d ", i); printbits(file, bs, test_length);
	}

	(void) fprintf(file, "\n");
	(void) fprintf(file, "1 bit should move right 1 position each line\n");
	for (i=0; i < test_length; i++) {
		bit_nclear(bs, 0, test_length - 1);
		bit_nset(bs, i, i);
		(void) fprintf(file, "%3d ", i); printbits(file, bs, test_length);
	}

	(void) free(bs);
}