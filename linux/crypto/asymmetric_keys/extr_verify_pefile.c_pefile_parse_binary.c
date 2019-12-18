#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct section_header {int dummy; } ;
struct pefile_context {unsigned long image_checksum_offset; size_t header_size; size_t n_data_dirents; unsigned long cert_dirent_offset; int certs_size; size_t sig_offset; int sig_len; size_t n_sections; struct section_header const* secs; } ;
struct pe_hdr {scalar_t__ magic; size_t sections; } ;
struct pe32plus_opt_hdr {size_t header_size; size_t data_dirs; int /*<<< orphan*/  csum; } ;
struct pe32_opt_hdr {int magic; size_t header_size; size_t data_dirs; int /*<<< orphan*/  csum; } ;
struct mz_hdr {scalar_t__ magic; size_t peaddr; } ;
struct data_dirent {int dummy; } ;
struct TYPE_2__ {int size; size_t virtual_address; } ;
struct data_directory {TYPE_1__ certs; } ;

/* Variables and functions */
 int ELIBBAD ; 
 int ENODATA ; 
 scalar_t__ MZ_MAGIC ; 
 scalar_t__ PE_MAGIC ; 
#define  PE_OPT_MAGIC_PE32 129 
#define  PE_OPT_MAGIC_PE32PLUS 128 
 int /*<<< orphan*/  chkaddr (size_t,size_t,int) ; 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int pefile_parse_binary(const void *pebuf, unsigned int pelen,
			       struct pefile_context *ctx)
{
	const struct mz_hdr *mz = pebuf;
	const struct pe_hdr *pe;
	const struct pe32_opt_hdr *pe32;
	const struct pe32plus_opt_hdr *pe64;
	const struct data_directory *ddir;
	const struct data_dirent *dde;
	const struct section_header *secs, *sec;
	size_t cursor, datalen = pelen;

	kenter("");

#define chkaddr(base, x, s)						\
	do {								\
		if ((x) < base || (s) >= datalen || (x) > datalen - (s)) \
			return -ELIBBAD;				\
	} while (0)

	chkaddr(0, 0, sizeof(*mz));
	if (mz->magic != MZ_MAGIC)
		return -ELIBBAD;
	cursor = sizeof(*mz);

	chkaddr(cursor, mz->peaddr, sizeof(*pe));
	pe = pebuf + mz->peaddr;
	if (pe->magic != PE_MAGIC)
		return -ELIBBAD;
	cursor = mz->peaddr + sizeof(*pe);

	chkaddr(0, cursor, sizeof(pe32->magic));
	pe32 = pebuf + cursor;
	pe64 = pebuf + cursor;

	switch (pe32->magic) {
	case PE_OPT_MAGIC_PE32:
		chkaddr(0, cursor, sizeof(*pe32));
		ctx->image_checksum_offset =
			(unsigned long)&pe32->csum - (unsigned long)pebuf;
		ctx->header_size = pe32->header_size;
		cursor += sizeof(*pe32);
		ctx->n_data_dirents = pe32->data_dirs;
		break;

	case PE_OPT_MAGIC_PE32PLUS:
		chkaddr(0, cursor, sizeof(*pe64));
		ctx->image_checksum_offset =
			(unsigned long)&pe64->csum - (unsigned long)pebuf;
		ctx->header_size = pe64->header_size;
		cursor += sizeof(*pe64);
		ctx->n_data_dirents = pe64->data_dirs;
		break;

	default:
		pr_debug("Unknown PEOPT magic = %04hx\n", pe32->magic);
		return -ELIBBAD;
	}

	pr_debug("checksum @ %x\n", ctx->image_checksum_offset);
	pr_debug("header size = %x\n", ctx->header_size);

	if (cursor >= ctx->header_size || ctx->header_size >= datalen)
		return -ELIBBAD;

	if (ctx->n_data_dirents > (ctx->header_size - cursor) / sizeof(*dde))
		return -ELIBBAD;

	ddir = pebuf + cursor;
	cursor += sizeof(*dde) * ctx->n_data_dirents;

	ctx->cert_dirent_offset =
		(unsigned long)&ddir->certs - (unsigned long)pebuf;
	ctx->certs_size = ddir->certs.size;

	if (!ddir->certs.virtual_address || !ddir->certs.size) {
		pr_debug("Unsigned PE binary\n");
		return -ENODATA;
	}

	chkaddr(ctx->header_size, ddir->certs.virtual_address,
		ddir->certs.size);
	ctx->sig_offset = ddir->certs.virtual_address;
	ctx->sig_len = ddir->certs.size;
	pr_debug("cert = %x @%x [%*ph]\n",
		 ctx->sig_len, ctx->sig_offset,
		 ctx->sig_len, pebuf + ctx->sig_offset);

	ctx->n_sections = pe->sections;
	if (ctx->n_sections > (ctx->header_size - cursor) / sizeof(*sec))
		return -ELIBBAD;
	ctx->secs = secs = pebuf + cursor;

	return 0;
}