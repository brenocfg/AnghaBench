#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int uncompressed_size; unsigned char treelevels; unsigned char* symbolsin; int symbol_size; int /*<<< orphan*/ * symbol_eob; int /*<<< orphan*/ * fpIn; int /*<<< orphan*/ ** tree; int /*<<< orphan*/ * symbol; int /*<<< orphan*/ * inodesin; int /*<<< orphan*/ * fpOut; } ;
typedef  TYPE_1__ unpack_descriptor_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EOF ; 
 unsigned char HTREE_MAXLEVEL ; 
 int PACK_HEADER_LENGTH ; 
 int /*<<< orphan*/  accepted_bytes (int /*<<< orphan*/ *,int) ; 
 void* calloc (int,int) ; 
 void* fdopen (int,char*) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  infile_newdata (scalar_t__) ; 
 int /*<<< orphan*/  maybe_err (char*) ; 
 int /*<<< orphan*/  maybe_errx (char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,size_t) ; 
 scalar_t__ read (int,unsigned char*,size_t) ; 
 int /*<<< orphan*/  unpackd_fill_inodesin (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unpack_parse_header(int in, int out, char *pre, size_t prelen, off_t *bytes_in,
    unpack_descriptor_t *unpackd)
{
	unsigned char hdr[PACK_HEADER_LENGTH];	/* buffer for header */
	ssize_t bytesread;		/* Bytes read from the file */
	int i, j, thisbyte;

	if (prelen > sizeof hdr)
		maybe_err("prelen too long");

	/* Prepend the header buffer if we already read some data */
	if (prelen != 0)
		memcpy(hdr, pre, prelen);

	/* Read in and fill the rest bytes of header */
	bytesread = read(in, hdr + prelen, PACK_HEADER_LENGTH - prelen);
	if (bytesread < 0)
		maybe_err("Error reading pack header");
	infile_newdata(bytesread);

	accepted_bytes(bytes_in, PACK_HEADER_LENGTH);

	/* Obtain uncompressed length (bytes 2,3,4,5) */
	unpackd->uncompressed_size = 0;
	for (i = 2; i <= 5; i++) {
		unpackd->uncompressed_size <<= 8;
		unpackd->uncompressed_size |= hdr[i];
	}

	/* Get the levels of the tree */
	unpackd->treelevels = hdr[6];
	if (unpackd->treelevels > HTREE_MAXLEVEL || unpackd->treelevels < 1)
		maybe_errx("Huffman tree has insane levels");

	/* Let libc take care for buffering from now on */
	if ((unpackd->fpIn = fdopen(in, "r")) == NULL)
		maybe_err("Can not fdopen() input stream");
	if ((unpackd->fpOut = fdopen(out, "w")) == NULL)
		maybe_err("Can not fdopen() output stream");

	/* Allocate for the tables of bounds and the tree itself */
	unpackd->inodesin =
	    calloc(unpackd->treelevels, sizeof(*(unpackd->inodesin)));
	unpackd->symbolsin =
	    calloc(unpackd->treelevels, sizeof(*(unpackd->symbolsin)));
	unpackd->tree =
	    calloc(unpackd->treelevels, (sizeof(*(unpackd->tree))));
	if (unpackd->inodesin == NULL || unpackd->symbolsin == NULL ||
	    unpackd->tree == NULL)
		maybe_err("calloc");

	/* We count from 0 so adjust to match array upper bound */
	unpackd->treelevels--;

	/* Read the levels symbol count table and calculate total */
	unpackd->symbol_size = 1;	/* EOB */
	for (i = 0; i <= unpackd->treelevels; i++) {
		if ((thisbyte = fgetc(unpackd->fpIn)) == EOF)
			maybe_err("File appears to be truncated");
		unpackd->symbolsin[i] = (unsigned char)thisbyte;
		unpackd->symbol_size += unpackd->symbolsin[i];
	}
	accepted_bytes(bytes_in, unpackd->treelevels);
	if (unpackd->symbol_size > 256)
		maybe_errx("Bad symbol table");
	infile_newdata(unpackd->treelevels);

	/* Allocate for the symbol table, point symbol_eob at the beginning */
	unpackd->symbol_eob = unpackd->symbol = calloc(1, unpackd->symbol_size);
	if (unpackd->symbol == NULL)
		maybe_err("calloc");

	/*
	 * Read in the symbol table, which contain [2, 256] symbols.
	 * In order to fit the count in one byte, pack(1) would offset
	 * it by reducing 2 from the actual number from the last level.
	 *
	 * We adjust the last level's symbol count by 1 here, because
	 * the EOB symbol is not being transmitted explicitly.  Another
	 * adjustment would be done later afterward.
	 */
	unpackd->symbolsin[unpackd->treelevels]++;
	for (i = 0; i <= unpackd->treelevels; i++) {
		unpackd->tree[i] = unpackd->symbol_eob;
		for (j = 0; j < unpackd->symbolsin[i]; j++) {
			if ((thisbyte = fgetc(unpackd->fpIn)) == EOF)
				maybe_errx("Symbol table truncated");
			*unpackd->symbol_eob++ = (char)thisbyte;
		}
		infile_newdata(unpackd->symbolsin[i]);
		accepted_bytes(bytes_in, unpackd->symbolsin[i]);
	}

	/* Now, take account for the EOB symbol as well */
	unpackd->symbolsin[unpackd->treelevels]++;

	/*
	 * The symbolsin table has been constructed now.
	 * Calculate the internal nodes count table based on it.
	 */
	unpackd_fill_inodesin(unpackd, 0);
}