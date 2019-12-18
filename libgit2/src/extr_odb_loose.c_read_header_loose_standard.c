#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ obj_hdr ;
typedef  int /*<<< orphan*/  inflated ;
typedef  int /*<<< orphan*/  git_zstream ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ git_rawobj ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ZSTREAM_INFLATE ; 
 int /*<<< orphan*/  GIT_ZSTREAM_INIT ; 
 int MAX_HEADER_LEN ; 
 int /*<<< orphan*/  git_zstream_free (int /*<<< orphan*/ *) ; 
 int git_zstream_get_output_chunk (unsigned char*,size_t*,int /*<<< orphan*/ *) ; 
 int git_zstream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_zstream_set_input (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int parse_header (TYPE_1__*,size_t*,unsigned char*,size_t) ; 

__attribute__((used)) static int read_header_loose_standard(
	git_rawobj *out, const unsigned char *data, size_t len)
{
	git_zstream zs = GIT_ZSTREAM_INIT;
	obj_hdr hdr;
	unsigned char inflated[MAX_HEADER_LEN];
	size_t header_len, inflated_len = sizeof(inflated);
	int error;

	if ((error = git_zstream_init(&zs, GIT_ZSTREAM_INFLATE)) < 0 ||
		(error = git_zstream_set_input(&zs, data, len)) < 0 ||
		(error = git_zstream_get_output_chunk(inflated, &inflated_len, &zs)) < 0 ||
		(error = parse_header(&hdr, &header_len, inflated, inflated_len)) < 0)
		goto done;

	out->len = hdr.size;
	out->type = hdr.type;

done:
	git_zstream_free(&zs);
	return error;
}