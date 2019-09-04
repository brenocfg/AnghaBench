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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct packed_git {int pack_fd; int do_not_close; int /*<<< orphan*/  pack_name; } ;
struct pack_header {scalar_t__ hdr_entries; void* hdr_version; void* hdr_signature; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct packed_git*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PACK_SIGNATURE ; 
 int /*<<< orphan*/  REALLOC_ARRAY (struct packed_git**,int) ; 
 struct strbuf STRBUF_INIT ; 
 struct packed_git** all_packs ; 
 int /*<<< orphan*/  hashfd (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite (int /*<<< orphan*/ ,struct pack_header*,int) ; 
 void* htonl (int) ; 
 scalar_t__ object_count ; 
 int odb_mkstemp (struct strbuf*,char*) ; 
 struct packed_git* pack_data ; 
 int /*<<< orphan*/  pack_file ; 
 int pack_id ; 
 int /*<<< orphan*/  pack_name ; 
 int pack_size ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void start_packfile(void)
{
	struct strbuf tmp_file = STRBUF_INIT;
	struct packed_git *p;
	struct pack_header hdr;
	int pack_fd;

	pack_fd = odb_mkstemp(&tmp_file, "pack/tmp_pack_XXXXXX");
	FLEX_ALLOC_STR(p, pack_name, tmp_file.buf);
	strbuf_release(&tmp_file);

	p->pack_fd = pack_fd;
	p->do_not_close = 1;
	pack_file = hashfd(pack_fd, p->pack_name);

	hdr.hdr_signature = htonl(PACK_SIGNATURE);
	hdr.hdr_version = htonl(2);
	hdr.hdr_entries = 0;
	hashwrite(pack_file, &hdr, sizeof(hdr));

	pack_data = p;
	pack_size = sizeof(hdr);
	object_count = 0;

	REALLOC_ARRAY(all_packs, pack_id + 1);
	all_packs[pack_id] = p;
}