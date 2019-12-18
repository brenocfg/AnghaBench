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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  ERRS (char*,char*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/ * board ; 
 int /*<<< orphan*/ * board_id ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_board (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int meraki_build_hdr (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int strip_padding ; 
 int /*<<< orphan*/  usage (int) ; 

int main(int argc, char *argv[])
{
	int ret = EXIT_FAILURE;
	char *ofname = NULL, *ifname = NULL;
	FILE *out, *in;
	size_t klen;

	progname = basename(argv[0]);

	while (1) {
		int c;

		c = getopt(argc, argv, "B:i:o:sh");
		if (c == -1)
			break;

		switch (c) {
		case 'B':
			board_id = optarg;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'o':
			ofname = optarg;
			break;
		case 's':
			strip_padding = true;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (board_id == NULL) {
		ERR("no board specified");
		goto err;
	}

	board = find_board(board_id);
	if (board == NULL) {
		ERR("unknown board \"%s\"", board_id);
		goto err;
	}

	if (ifname == NULL) {
		ERR("no input file specified");
		goto err;
	}

	if (ofname == NULL) {
		ERR("no output file specified");
		goto err;
	}

	in = fopen(ifname, "r");
	if (in == NULL) {
		ERRS("could not open \"%s\" for reading: %s", ifname);
		goto err;
	}

	/* Get kernel length */
	fseek(in, 0, SEEK_END);
	klen = ftell(in);
	rewind(in);

	out = fopen(ofname, "w");
	if (out == NULL) {
		ERRS("could not open \"%s\" for writing: %s", ofname);
		goto err_close_in;
	}

	ret = meraki_build_hdr(board, klen, out, in);
	fclose(out);

err_close_in:
	fclose(in);

err:
	return ret;
}