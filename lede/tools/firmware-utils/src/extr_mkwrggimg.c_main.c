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
struct wrgg03_header {int /*<<< orphan*/  devname; int /*<<< orphan*/  offset; int /*<<< orphan*/  size; int /*<<< orphan*/  buildno; int /*<<< orphan*/  reserve; int /*<<< orphan*/  flag; int /*<<< orphan*/  model; int /*<<< orphan*/  version; int /*<<< orphan*/  magic2; int /*<<< orphan*/  magic1; int /*<<< orphan*/  signature; } ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERRS (char*,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int WRGG03_MAGIC ; 
 int /*<<< orphan*/  basename (char*) ; 
 int big_endian ; 
 int /*<<< orphan*/ * buildno ; 
 int /*<<< orphan*/ * devname ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int flag ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_digest (struct wrgg03_header*,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * ifname ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memset (struct wrgg03_header*,char,int) ; 
 int /*<<< orphan*/ * model ; 
 int offset ; 
 int /*<<< orphan*/ * ofname ; 
 void* optarg ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  put_u32 (int /*<<< orphan*/ *,int,int) ; 
 int reserve ; 
 int /*<<< orphan*/ * signature ; 
 int stat (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int strtoul (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/ * version ; 

int main(int argc, char *argv[])
{
	struct wrgg03_header *header;
	char *buf;
	struct stat st;
	int buflen;
	int err;
	int res = EXIT_FAILURE;

	FILE *outfile, *infile;

	progname = basename(argv[0]);

	while ( 1 ) {
		int c;

		c = getopt(argc, argv, "bd:i:m:o:s:v:B:O:h");
		if (c == -1)
			break;

		switch (c) {
		case 'b':
			big_endian = 1;
			break;
		case 'B':
			buildno = optarg;
			break;
		case 'd':
			devname = optarg;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'm':
			model = optarg;
			break;
		case 'o':
			ofname = optarg;
			break;
		case 's':
			signature = optarg;
			break;
		case 'v':
			version = optarg;
			break;
		case 'O':
			offset = strtoul(optarg, NULL, 0);
			break;
		case 'h':
			usage(EXIT_SUCCESS);
			break;

		default:
			usage(EXIT_FAILURE);
			break;
		}
	}

	if (signature == NULL) {
		ERR("no signature specified");
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

	if (devname == NULL) {
		ERR("no device name specified");
		goto err;
	}

	if (model == NULL) {
		ERR("no model name specified");
		goto err;
	}

	if (buildno == NULL) {
		ERR("no build number specified");
		goto err;
	}

	if (version == NULL) {
		ERR("no version specified");
		goto err;
	}

	err = stat(ifname, &st);
	if (err){
		ERRS("stat failed on %s", ifname);
		goto err;
	}

	buflen = st.st_size + sizeof(struct wrgg03_header);
	buf = malloc(buflen);
	if (!buf) {
		ERR("no memory for buffer\n");
		goto err;
	}

	infile = fopen(ifname, "r");
	if (infile == NULL) {
		ERRS("could not open \"%s\" for reading", ifname);
		goto err_free;
	}

	errno = 0;
	fread(buf + sizeof(struct wrgg03_header), st.st_size, 1, infile);
	if (errno != 0) {
		ERRS("unable to read from file %s", ifname);
		goto close_in;
	}

	header = (struct wrgg03_header *) buf;
	memset(header, '\0', sizeof(struct wrgg03_header));

	strncpy(header->signature, signature, sizeof(header->signature));
	put_u32(&header->magic1, WRGG03_MAGIC, 0);
	put_u32(&header->magic2, WRGG03_MAGIC, 0);
	strncpy(header->version, version, sizeof(header->version));
	strncpy(header->model, model, sizeof(header->model));
	put_u32(&header->flag, flag, 0);
	put_u32(&header->reserve, reserve, 0);
	strncpy(header->buildno, buildno, sizeof(header->buildno));
	put_u32(&header->size, st.st_size, big_endian);
	put_u32(&header->offset, offset, big_endian);
	strncpy(header->devname, devname, sizeof(header->devname));

	get_digest(header, buf + sizeof(struct wrgg03_header), st.st_size);

	outfile = fopen(ofname, "w");
	if (outfile == NULL) {
		ERRS("could not open \"%s\" for writing", ofname);
		goto close_in;
	}

	errno = 0;
	fwrite(buf, buflen, 1, outfile);
	if (errno) {
		ERRS("unable to write to file %s", ofname);
		goto close_out;
	}

	fflush(outfile);

	res = EXIT_SUCCESS;

close_out:
	fclose(outfile);
	if (res != EXIT_SUCCESS)
		unlink(ofname);
close_in:
	fclose(infile);
err_free:
	free(buf);
err:
	return res;
}