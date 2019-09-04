#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_push ;
struct TYPE_7__ {char const* data; size_t len; } ;
typedef  TYPE_1__ git_pkt_data ;
typedef  int /*<<< orphan*/  git_pkt ;
struct TYPE_8__ {size_t size; char* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int GIT_EBUFS ; 
 int GIT_ITEROVER ; 
 int add_push_report_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_consume (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  git_pkt_free (int /*<<< orphan*/ *) ; 
 int git_pkt_parse_line (int /*<<< orphan*/ **,char const**,char const*,size_t) ; 

__attribute__((used)) static int add_push_report_sideband_pkt(git_push *push, git_pkt_data *data_pkt, git_buf *data_pkt_buf)
{
	git_pkt *pkt;
	const char *line, *line_end = NULL;
	size_t line_len;
	int error;
	int reading_from_buf = data_pkt_buf->size > 0;

	if (reading_from_buf) {
		/* We had an existing partial packet, so add the new
		 * packet to the buffer and parse the whole thing */
		git_buf_put(data_pkt_buf, data_pkt->data, data_pkt->len);
		line = data_pkt_buf->ptr;
		line_len = data_pkt_buf->size;
	}
	else {
		line = data_pkt->data;
		line_len = data_pkt->len;
	}

	while (line_len > 0) {
		error = git_pkt_parse_line(&pkt, &line_end, line, line_len);

		if (error == GIT_EBUFS) {
			/* Buffer the data when the inner packet is split
			 * across multiple sideband packets */
			if (!reading_from_buf)
				git_buf_put(data_pkt_buf, line, line_len);
			error = 0;
			goto done;
		}
		else if (error < 0)
			goto done;

		/* Advance in the buffer */
		line_len -= (line_end - line);
		line = line_end;

		error = add_push_report_pkt(push, pkt);

		git_pkt_free(pkt);

		if (error < 0 && error != GIT_ITEROVER)
			goto done;
	}

	error = 0;

done:
	if (reading_from_buf)
		git_buf_consume(data_pkt_buf, line_end);
	return error;
}