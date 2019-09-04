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
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int MAX_HEADER_LEN ; 
 scalar_t__ freshen_loose_object (struct object_id*) ; 
 scalar_t__ freshen_packed_object (struct object_id*) ; 
 int write_loose_object (struct object_id*,char*,int,void const*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_object_file_prepare (void const*,unsigned long,char const*,struct object_id*,char*,int*) ; 

int write_object_file(const void *buf, unsigned long len, const char *type,
		      struct object_id *oid)
{
	char hdr[MAX_HEADER_LEN];
	int hdrlen = sizeof(hdr);

	/* Normally if we have it in the pack then we do not bother writing
	 * it out into .git/objects/??/?{38} file.
	 */
	write_object_file_prepare(buf, len, type, oid, hdr, &hdrlen);
	if (freshen_packed_object(oid) || freshen_loose_object(oid))
		return 0;
	return write_loose_object(oid, hdr, hdrlen, buf, len, 0);
}