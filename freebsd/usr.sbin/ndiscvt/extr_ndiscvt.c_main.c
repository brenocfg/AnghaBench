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
 scalar_t__ IFNAMSIZ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  bincvt (char*,char*,void*,int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  firmcvt (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ inf_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ insert_padding (void**,int*) ; 
 char* optarg ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	FILE			*fp, *outfp;
	int			i, bin = 0;
	void			*img;
	int			n, fsize, cnt;
	unsigned char		*ptr;
	char			*inffile = NULL, *sysfile = NULL;
	char			*outfile = NULL, *firmfile = NULL;
	char			*dname = NULL;
	int			ch;

	while((ch = getopt(argc, argv, "i:s:o:n:f:O")) != -1) {
		switch(ch) {
		case 'f':
			firmfile = optarg;
			break;
		case 'i':
			inffile = optarg;
			break;
		case 's':
			sysfile = optarg;
			break;
		case 'o':
			outfile = optarg;
			break;
		case 'n':
			dname = optarg;
			break;
		case 'O':
			bin = 1;
			break;
		default:
			usage();
			break;
		}
	}

	if (firmfile != NULL)
		firmcvt(firmfile);

	if (sysfile == NULL)
		usage();

	/* Open the .SYS file and load it into memory */
	fp = fopen(sysfile, "r");
	if (fp == NULL)
		err(1, "opening .SYS file '%s' failed", sysfile);
	fseek (fp, 0L, SEEK_END);
	fsize = ftell (fp);
	rewind (fp);
	img = calloc(fsize, 1);
	n = fread (img, fsize, 1, fp);
	if (n == 0)
		err(1, "reading .SYS file '%s' failed", sysfile);

	fclose(fp);

	if (insert_padding(&img, &fsize)) {
		fprintf(stderr, "section relocation failed\n");
		exit(1);
	}

	if (outfile == NULL || strcmp(outfile, "-") == 0)
		outfp = stdout;
	else {
		outfp = fopen(outfile, "w");
		if (outfp == NULL)
			err(1, "opening output file '%s' failed", outfile);
	}

	fprintf(outfp, "\n/*\n");
	fprintf(outfp, " * Generated from %s and %s (%d bytes)\n",
	    inffile == NULL ? "<notused>" : inffile, sysfile, fsize);
	fprintf(outfp, " */\n\n");

	if (dname != NULL) {
		if (strlen(dname) > IFNAMSIZ)
			err(1, "selected device name '%s' is "
			    "too long (max chars: %d)", dname, IFNAMSIZ);
		fprintf (outfp, "#define NDIS_DEVNAME \"%s\"\n", dname);
		fprintf (outfp, "#define NDIS_MODNAME %s\n\n", dname);
	}

	if (inffile == NULL) {
		fprintf (outfp, "#ifdef NDIS_REGVALS\n");
		fprintf (outfp, "ndis_cfg ndis_regvals[] = {\n");
        	fprintf (outfp, "\t{ NULL, NULL, { 0 }, 0 }\n");
		fprintf (outfp, "#endif /* NDIS_REGVALS */\n");

		fprintf (outfp, "};\n\n");
	} else {
		fp = fopen(inffile, "r");
		if (fp == NULL)
			err(1, "opening .INF file '%s' failed", inffile);


		if (inf_parse(fp, outfp) != 0)
			errx(1, "creating .INF file - no entries created, are you using the correct files?");
		fclose(fp);
	}

	fprintf(outfp, "\n#ifdef NDIS_IMAGE\n");

	if (bin) {
		sysfile = strdup(basename(sysfile));
		ptr = (unsigned char *)sysfile;
		while (*ptr) {
			if (*ptr == '.')
				*ptr = '_';
			ptr++;
		}
		fprintf(outfp,
		    "\nextern unsigned char ndis_%s_drv_data_start[];\n",
		    sysfile);
		fprintf(outfp, "static unsigned char *drv_data = "
		    "ndis_%s_drv_data_start;\n\n", sysfile);
		bincvt(sysfile, outfile, img, fsize);
		goto done;
	}


	fprintf(outfp, "\nextern unsigned char drv_data[];\n\n");

	fprintf(outfp, "__asm__(\".data\");\n");
	fprintf(outfp, "__asm__(\".globl  drv_data\");\n");
	fprintf(outfp, "__asm__(\".type   drv_data, @object\");\n");
	fprintf(outfp, "__asm__(\".size   drv_data, %d\");\n", fsize);
	fprintf(outfp, "__asm__(\"drv_data:\");\n");

	ptr = img;
	cnt = 0;
	while(cnt < fsize) {
		fprintf (outfp, "__asm__(\".byte ");
		for (i = 0; i < 10; i++) {
			cnt++;
			if (cnt == fsize) {
				fprintf(outfp, "0x%.2X\");\n", ptr[i]);
				goto done;
			} else {
				if (i == 9)
					fprintf(outfp, "0x%.2X\");\n", ptr[i]);
				else
					fprintf(outfp, "0x%.2X, ", ptr[i]);
			}
		}
		ptr += 10;
	}

done:

	fprintf(outfp, "#endif /* NDIS_IMAGE */\n");

	if (fp != NULL)
		fclose(fp);
	fclose(outfp);
	free(img);
	exit(0);
}