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
typedef  int uint32_t ;
struct sysinit_data {scalar_t__* b_debug_info; scalar_t__* b_file_name; scalar_t__* b_global_name; scalar_t__* b_global_type; scalar_t__* b_keyword_name; void* dw_file_line; void* dw_msb_value; void* dw_lsb_value; int /*<<< orphan*/  dw_endian32; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  compare ; 
 int /*<<< orphan*/  compare_R ; 
 void* do_malloc (int) ; 
 int /*<<< orphan*/  do_sysinit () ; 
 int /*<<< orphan*/  endian32 ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * input_f ; 
 scalar_t__ input_file ; 
 int input_len ; 
 void* input_ptr ; 
 int /*<<< orphan*/ * keyword ; 
 scalar_t__ lseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ open (int /*<<< orphan*/ *,int,...) ; 
 scalar_t__ opt_R ; 
 void* optarg ; 
 int /*<<< orphan*/ * output_f ; 
 scalar_t__ output_file ; 
 int /*<<< orphan*/  qsort (struct sysinit_data**,int,int,int /*<<< orphan*/ *) ; 
 int read (scalar_t__,void*,int) ; 
 void* read32 (void*) ; 
 struct sysinit_data** start ; 
 struct sysinit_data** stop ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * struct_name ; 
 int success ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	struct sysinit_data **sipp;
	int c;
	int entries;
	off_t off;

	while ((c = getopt(argc, argv, "k:s:i:o:Rh")) != -1) {
		switch (c) {
		case 'i':
			input_f = optarg;
			break;
		case 'o':
			output_f = optarg;
			break;
		case 'R':
			opt_R = 1;
			break;
		case 'k':
			keyword = optarg;
			break;
		case 's':
			struct_name = optarg;
			break;
		default:
			usage();
		}
	}

	if (input_f == NULL || output_f == NULL ||
	    struct_name == NULL || keyword == NULL)
		usage();

	atexit(&cleanup);

	cleanup();

	input_file = open(input_f, O_RDONLY);
	if (input_file < 0)
		err(EX_SOFTWARE, "Could not open input file: %s", input_f);

	output_file = open(output_f, O_TRUNC | O_CREAT | O_RDWR, 0600);
	if (output_file < 0)
		err(EX_SOFTWARE, "Could not open output file: %s", output_f);

	off = lseek(input_file, 0, SEEK_END);

	input_ptr = do_malloc(off);
	input_len = off;

	if (input_len % (uint32_t)sizeof(struct sysinit_data)) {
		errx(EX_SOFTWARE, "Input file size is not divisible by %u",
		    (unsigned int)sizeof(struct sysinit_data));
	}
	off = lseek(input_file, 0, SEEK_SET);
	if (off < 0)
		err(EX_SOFTWARE, "Could not seek to start of input file");

	if (read(input_file, input_ptr, input_len) != input_len)
		err(EX_SOFTWARE, "Could not read input file");

	entries = input_len / (uint32_t)sizeof(struct sysinit_data);

	start = do_malloc(sizeof(void *) * entries);
	stop = start + entries;

	for (c = 0; c != entries; c++)
		start[c] = &((struct sysinit_data *)input_ptr)[c];

	if (start != stop)
		endian32 = (*start)->dw_endian32;

	/* switch all fields to host endian order */
	for (sipp = start; sipp < stop; sipp++) {
		(*sipp)->dw_lsb_value = read32((*sipp)->dw_lsb_value);
		(*sipp)->dw_msb_value = read32((*sipp)->dw_msb_value);
		(*sipp)->dw_file_line = read32((*sipp)->dw_file_line);
	}

	if (opt_R == 0) {
		/* sort entries, rising numerical order */
		qsort(start, entries, sizeof(void *), &compare);
	} else {
		/* sort entries, falling numerical order */
		qsort(start, entries, sizeof(void *), &compare_R);
	}

	/* safe all strings */
	for (sipp = start; sipp < stop; sipp++) {
		(*sipp)->b_keyword_name[sizeof((*sipp)->b_keyword_name) - 1] = 0;
		(*sipp)->b_global_type[sizeof((*sipp)->b_global_type) - 1] = 0;
		(*sipp)->b_global_name[sizeof((*sipp)->b_global_name) - 1] = 0;
		(*sipp)->b_file_name[sizeof((*sipp)->b_file_name) - 1] = 0;
		(*sipp)->b_debug_info[sizeof((*sipp)->b_debug_info) - 1] = 0;
	}

	if (strcmp(keyword, "sysinit") == 0)
		do_sysinit();
	else if (strcmp(keyword, "sysuninit") == 0)
		do_sysinit();
	else
		errx(EX_USAGE, "Unknown keyword '%s'", keyword);

	success = 1;

	return (0);
}