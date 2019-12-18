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
struct stat {unsigned int st_size; } ;
struct pc1_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int BUFSIZE ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERRS (char*,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  basename (char*) ; 
 int decrypt ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fread (char*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * ifname ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/ * ofname ; 
 int /*<<< orphan*/ * optarg ; 
 int /*<<< orphan*/  pc1_decrypt_buf (struct pc1_ctx*,char*,unsigned int) ; 
 int /*<<< orphan*/  pc1_encrypt_buf (struct pc1_ctx*,char*,unsigned int) ; 
 int /*<<< orphan*/  pc1_finish (struct pc1_ctx*) ; 
 int /*<<< orphan*/  pc1_init (struct pc1_ctx*) ; 
 int /*<<< orphan*/  progname ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 

int main(int argc, char *argv[])
{
	struct pc1_ctx pc1;
	int res = EXIT_FAILURE;
	int err;
	struct stat st;
	char *buf;
	unsigned total;

	FILE *outfile, *infile;

	progname = basename(argv[0]);

	while ( 1 ) {
		int c;

		c = getopt(argc, argv, "di:o:h");
		if (c == -1)
			break;

		switch (c) {
		case 'd':
			decrypt = 1;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'o':
			ofname = optarg;
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;
		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (ifname == NULL) {
		ERR("no input file specified");
		goto err;
	}

	if (ofname == NULL) {
		ERR("no output file specified");
		goto err;
	}

	err = stat(ifname, &st);
	if (err){
		ERRS("stat failed on %s", ifname);
		goto err;
	}

	total = st.st_size;
	buf = malloc(BUFSIZE);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto err;
	}

	infile = fopen(ifname, "r");
	if (infile == NULL) {
		ERRS("could not open \"%s\" for reading", ifname);
		goto err_free;
	}

	outfile = fopen(ofname, "w");
	if (outfile == NULL) {
		ERRS("could not open \"%s\" for writing", ofname);
		goto err_close_in;
	}

	pc1_init(&pc1);
	while (total > 0) {
		unsigned datalen;

		if (total > BUFSIZE)
			datalen = BUFSIZE;
		else
			datalen = total;

		errno = 0;
		fread(buf, datalen, 1, infile);
		if (errno != 0) {
			ERRS("unable to read from file %s", ifname);
			goto err_close_out;
		}

		if (decrypt)
			pc1_decrypt_buf(&pc1, buf, datalen);
		else
			pc1_encrypt_buf(&pc1, buf, datalen);

		errno = 0;
		fwrite(buf, datalen, 1, outfile);
		if (errno) {
			ERRS("unable to write to file %s", ofname);
			goto err_close_out;
		}

		total -= datalen;
	}
	pc1_finish(&pc1);

	res = EXIT_SUCCESS;

 out_flush:
	fflush(outfile);

 err_close_out:
	fclose(outfile);
	if (res != EXIT_SUCCESS) {
		unlink(ofname);
	}

 err_close_in:
	fclose(infile);

 err_free:
	free(buf);

 err:
	return res;
}