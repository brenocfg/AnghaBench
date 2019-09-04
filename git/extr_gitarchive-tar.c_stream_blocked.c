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
struct git_istream {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BLOCKSIZE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close_istream (struct git_istream*) ; 
 int /*<<< orphan*/  do_write_blocked (char*,scalar_t__) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_record () ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct git_istream* open_istream (struct object_id const*,int*,unsigned long*,int /*<<< orphan*/ *) ; 
 scalar_t__ read_istream (struct git_istream*,char*,int) ; 

__attribute__((used)) static int stream_blocked(const struct object_id *oid)
{
	struct git_istream *st;
	enum object_type type;
	unsigned long sz;
	char buf[BLOCKSIZE];
	ssize_t readlen;

	st = open_istream(oid, &type, &sz, NULL);
	if (!st)
		return error(_("cannot stream blob %s"), oid_to_hex(oid));
	for (;;) {
		readlen = read_istream(st, buf, sizeof(buf));
		if (readlen <= 0)
			break;
		do_write_blocked(buf, readlen);
	}
	close_istream(st);
	if (!readlen)
		finish_record();
	return readlen;
}