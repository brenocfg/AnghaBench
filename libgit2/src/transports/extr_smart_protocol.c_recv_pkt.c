#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* data; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ gitno_buffer ;
typedef  int /*<<< orphan*/  git_pkt_type ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_pkt ;

/* Variables and functions */
 int GIT_EBUFS ; 
 int GIT_EEOF ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_pkt_parse_line (TYPE_2__**,char const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gitno_consume (TYPE_1__*,char const*) ; 
 int gitno_recv (TYPE_1__*) ; 

__attribute__((used)) static int recv_pkt(git_pkt **out_pkt, git_pkt_type *out_type, gitno_buffer *buf)
{
	const char *ptr = buf->data, *line_end = ptr;
	git_pkt *pkt = NULL;
	int error = 0, ret;

	do {
		if (buf->offset > 0)
			error = git_pkt_parse_line(&pkt, &line_end, ptr, buf->offset);
		else
			error = GIT_EBUFS;

		if (error == 0)
			break; /* return the pkt */

		if (error < 0 && error != GIT_EBUFS)
			return error;

		if ((ret = gitno_recv(buf)) < 0) {
			return ret;
		} else if (ret == 0) {
			git_error_set(GIT_ERROR_NET, "early EOF");
			return GIT_EEOF;
		}
	} while (error);

	gitno_consume(buf, line_end);
	if (out_type != NULL)
		*out_type = pkt->type;
	if (out_pkt != NULL)
		*out_pkt = pkt;
	else
		git__free(pkt);

	return error;
}