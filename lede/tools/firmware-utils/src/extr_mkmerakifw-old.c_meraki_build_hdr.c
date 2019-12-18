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
struct board_info {size_t imagelen; size_t const magic; size_t const load_addr; size_t const entry; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t) ; 
 int /*<<< orphan*/  ERRS (char*) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 size_t HDR_LENGTH ; 
 int /*<<< orphan*/  HDR_OFF_CHECKSUM ; 
 int /*<<< orphan*/  HDR_OFF_ENTRY ; 
 int /*<<< orphan*/  HDR_OFF_FILLER0 ; 
 int /*<<< orphan*/  HDR_OFF_FILLER1 ; 
 int /*<<< orphan*/  HDR_OFF_FILLER2 ; 
 int /*<<< orphan*/  HDR_OFF_IMAGELEN ; 
 int /*<<< orphan*/  HDR_OFF_LOAD_ADDR ; 
 int /*<<< orphan*/  HDR_OFF_MAGIC1 ; 
 int /*<<< orphan*/  PADDING_BYTE ; 
 int /*<<< orphan*/  crc32_csum (unsigned char*,size_t const) ; 
 int /*<<< orphan*/  fread (unsigned char*,size_t const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 size_t fwrite (unsigned char*,size_t,int,int /*<<< orphan*/ *) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ strip_padding ; 
 int /*<<< orphan*/  writel (unsigned char*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static int meraki_build_hdr(const struct board_info *board, const size_t klen,
			    FILE *out, FILE *in)
{
	unsigned char *kernel;
	unsigned char *buf;
	size_t buflen;
	size_t kspace;

	size_t rc;
	buflen = board->imagelen;
	kspace = buflen - HDR_LENGTH;

	if (klen > kspace) {
		ERR("kernel file is too big - max size: 0x%08lX\n", kspace);
		return EXIT_FAILURE;
	}

	/* If requested, resize buffer to remove padding */
	if (strip_padding)
		buflen = klen + HDR_LENGTH;

	/* Allocate and initialize buffer for final image */
	buf = malloc(buflen);
	if (buf == NULL) {
		ERRS("no memory for buffer: %s\n");
		return EXIT_FAILURE;
	}
	memset(buf, PADDING_BYTE, buflen);

	/* Load kernel */
	kernel = buf + HDR_LENGTH;
	fread(kernel, klen, 1, in);

	/* Write magic values and filler */
	writel(buf, HDR_OFF_MAGIC1, board->magic);
	writel(buf, HDR_OFF_FILLER0, 0);
	writel(buf, HDR_OFF_FILLER1, 0);
	writel(buf, HDR_OFF_FILLER2, 0);

	/* Write load and kernel entry point address */
	writel(buf, HDR_OFF_LOAD_ADDR, board->load_addr);
	writel(buf, HDR_OFF_ENTRY, board->entry);

	/* Write header and image length */
	writel(buf, HDR_OFF_IMAGELEN, klen);

	/* this gets replaced later, after the checksum has been calculated */
	writel(buf, HDR_OFF_CHECKSUM, 0);

	/* Write checksum */
	crc32_csum(buf, klen + HDR_LENGTH);

	rc = fwrite(buf, buflen, 1, out);

	free(buf);

	return rc == 1 ? EXIT_SUCCESS : EXIT_FAILURE;
}