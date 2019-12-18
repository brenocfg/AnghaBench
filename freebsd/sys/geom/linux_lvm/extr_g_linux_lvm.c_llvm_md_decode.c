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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
struct g_llvm_metadata {int md_version; scalar_t__ md_size; scalar_t__ md_start; scalar_t__ md_relsize; scalar_t__ md_reloffset; void* md_csum; } ;
struct g_llvm_label {scalar_t__ ll_md_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  G_LLVM_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  G_LLVM_MAGIC ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,char*,int) ; 
 void* le32dec (int /*<<< orphan*/  const*) ; 
 scalar_t__ le64dec (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
llvm_md_decode(const u_char *data, struct g_llvm_metadata *md,
    struct g_llvm_label *ll)
{
	uint64_t off;
	char magic[16];

	off = 0;
	md->md_csum = le32dec(data + off);
	off += 4;
	bcopy(data + off, magic, 16);
	off += 16;
	md->md_version = le32dec(data + off);
	off += 4;
	md->md_start = le64dec(data + off);
	off += 8;
	md->md_size = le64dec(data + off);
	off += 8;

	if (bcmp(G_LLVM_MAGIC, magic, 16) != 0) {
		G_LLVM_DEBUG(0, "Incorrect md magic number");
		return (EINVAL);
	}
	if (md->md_version != 1) {
		G_LLVM_DEBUG(0, "Incorrect md version number (%u)",
		    md->md_version);
		return (EINVAL);
	}
	if (md->md_start != ll->ll_md_offset) {
		G_LLVM_DEBUG(0, "Incorrect md offset (%ju)", md->md_start);
		return (EINVAL);
	}

	/* Aparently only one is ever returned */
	md->md_reloffset = le64dec(data + off);
	off += 8;
	md->md_relsize = le64dec(data + off);
	off += 16;	/* XXX skipped checksum */

	if (le64dec(data + off) != 0) {
		G_LLVM_DEBUG(0, "Only one reloc supported");
		return (EINVAL);
	}

	G_LLVM_DEBUG(3, "reloc: offset=%ju, size=%ju",
	    md->md_reloffset, md->md_relsize);
	G_LLVM_DEBUG(3, "md: version=%u, start=%ju, size=%ju",
	    md->md_version, md->md_start, md->md_size);

	return (0);
}