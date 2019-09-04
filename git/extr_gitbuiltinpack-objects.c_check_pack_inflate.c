#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct packed_git {int dummy; } ;
struct pack_window {int dummy; } ;
typedef  int /*<<< orphan*/  stream ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {unsigned char* next_in; unsigned char* next_out; int avail_out; unsigned long total_out; scalar_t__ total_in; int /*<<< orphan*/  avail_in; } ;
typedef  TYPE_1__ git_zstream ;
typedef  int /*<<< orphan*/  fakebuf ;

/* Variables and functions */
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int git_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_inflate_end (TYPE_1__*) ; 
 int /*<<< orphan*/  git_inflate_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 unsigned char* use_pack (struct packed_git*,struct pack_window**,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_pack_inflate(struct packed_git *p,
		struct pack_window **w_curs,
		off_t offset,
		off_t len,
		unsigned long expect)
{
	git_zstream stream;
	unsigned char fakebuf[4096], *in;
	int st;

	memset(&stream, 0, sizeof(stream));
	git_inflate_init(&stream);
	do {
		in = use_pack(p, w_curs, offset, &stream.avail_in);
		stream.next_in = in;
		stream.next_out = fakebuf;
		stream.avail_out = sizeof(fakebuf);
		st = git_inflate(&stream, Z_FINISH);
		offset += stream.next_in - in;
	} while (st == Z_OK || st == Z_BUF_ERROR);
	git_inflate_end(&stream);
	return (st == Z_STREAM_END &&
		stream.total_out == expect &&
		stream.total_in == len) ? 0 : -1;
}