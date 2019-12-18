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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct g_journal_record_header {scalar_t__ jrh_nentries; struct g_journal_entry* jrh_entries; int /*<<< orphan*/  jrh_sum; int /*<<< orphan*/  jrh_journal_id; int /*<<< orphan*/  jrh_magic; } ;
struct g_journal_entry {void* je_length; void* je_offset; void* je_joffset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GJ_RECORD_HEADER_MAGIC ; 
 scalar_t__ GJ_RECORD_HEADER_NENTRIES ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ le16dec (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  le32dec (int /*<<< orphan*/  const*) ; 
 void* le64dec (int /*<<< orphan*/  const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_journal_record_header_decode(const u_char *data,
    struct g_journal_record_header *hdr)
{
	struct g_journal_entry *ent;
	u_int i;

	bcopy(data, hdr->jrh_magic, sizeof(hdr->jrh_magic));
	data += sizeof(hdr->jrh_magic);
	if (strcmp(hdr->jrh_magic, GJ_RECORD_HEADER_MAGIC) != 0)
		return (EINVAL);
	hdr->jrh_journal_id = le32dec(data);
	data += 8;
	hdr->jrh_nentries = le16dec(data);
	data += 2;
	if (hdr->jrh_nentries > GJ_RECORD_HEADER_NENTRIES)
		return (EINVAL);
	bcopy(data, hdr->jrh_sum, sizeof(hdr->jrh_sum));
	data += 8;
	for (i = 0; i < hdr->jrh_nentries; i++) {
		ent = &hdr->jrh_entries[i];
		ent->je_joffset = le64dec(data);
		data += 8;
		ent->je_offset = le64dec(data);
		data += 8;
		ent->je_length = le64dec(data);
		data += 8;
	}
	return (0);
}