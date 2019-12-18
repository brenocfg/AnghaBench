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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {unsigned char* next_out; int avail_out; int total_out; unsigned char* next_in; int /*<<< orphan*/  avail_in; } ;
typedef  TYPE_1__ git_zstream ;
typedef  int /*<<< orphan*/  delta_head ;

/* Variables and functions */
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  error (char*) ; 
 unsigned long get_delta_hdr_size (unsigned char const**,unsigned char*) ; 
 int git_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_inflate_end (TYPE_1__*) ; 
 int /*<<< orphan*/  git_inflate_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 unsigned char* use_pack (struct packed_git*,struct pack_window**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned long get_size_from_delta(struct packed_git *p,
				  struct pack_window **w_curs,
				  off_t curpos)
{
	const unsigned char *data;
	unsigned char delta_head[20], *in;
	git_zstream stream;
	int st;

	memset(&stream, 0, sizeof(stream));
	stream.next_out = delta_head;
	stream.avail_out = sizeof(delta_head);

	git_inflate_init(&stream);
	do {
		in = use_pack(p, w_curs, curpos, &stream.avail_in);
		stream.next_in = in;
		st = git_inflate(&stream, Z_FINISH);
		curpos += stream.next_in - in;
	} while ((st == Z_OK || st == Z_BUF_ERROR) &&
		 stream.total_out < sizeof(delta_head));
	git_inflate_end(&stream);
	if ((st != Z_STREAM_END) && stream.total_out != sizeof(delta_head)) {
		error("delta data unpack-initial failed");
		return 0;
	}

	/* Examine the initial part of the delta to figure out
	 * the result size.
	 */
	data = delta_head;

	/* ignore base size */
	get_delta_hdr_size(&data, delta_head+sizeof(delta_head));

	/* Read the result size */
	return get_delta_hdr_size(&data, delta_head+sizeof(delta_head));
}