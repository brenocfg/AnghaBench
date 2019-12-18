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

/* Variables and functions */
 unsigned int HASH_WRITE_OBJECT ; 
 int MAX_HEADER_LEN ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ freshen_loose_object (struct object_id*) ; 
 scalar_t__ freshen_packed_object (struct object_id*) ; 
 int strlen (char const*) ; 
 int write_loose_object (struct object_id*,char*,int,void const*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_object_file_prepare (void const*,unsigned long,char const*,struct object_id*,char*,int*) ; 
 char* xmalloc (int) ; 

int hash_object_file_literally(const void *buf, unsigned long len,
			       const char *type, struct object_id *oid,
			       unsigned flags)
{
	char *header;
	int hdrlen, status = 0;

	/* type string, SP, %lu of the length plus NUL must fit this */
	hdrlen = strlen(type) + MAX_HEADER_LEN;
	header = xmalloc(hdrlen);
	write_object_file_prepare(buf, len, type, oid, header, &hdrlen);

	if (!(flags & HASH_WRITE_OBJECT))
		goto cleanup;
	if (freshen_packed_object(oid) || freshen_loose_object(oid))
		goto cleanup;
	status = write_loose_object(oid, header, hdrlen, buf, len, 0);

cleanup:
	free(header);
	return status;
}