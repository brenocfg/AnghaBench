#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  oid; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_ack ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ACK_COMMON ; 
 int /*<<< orphan*/  GIT_ACK_CONTINUE ; 
 int /*<<< orphan*/  GIT_ACK_READY ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 size_t GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  GIT_PKT_ACK ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 scalar_t__ git__prefixncmp (char const*,size_t,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int ack_pkt(git_pkt **out, const char *line, size_t len)
{
	git_pkt_ack *pkt;

	pkt = git__calloc(1, sizeof(git_pkt_ack));
	GIT_ERROR_CHECK_ALLOC(pkt);
	pkt->type = GIT_PKT_ACK;

	if (git__prefixncmp(line, len, "ACK "))
		goto out_err;
	line += 4;
	len -= 4;

	if (len < GIT_OID_HEXSZ || git_oid_fromstr(&pkt->oid, line) < 0)
		goto out_err;
	line += GIT_OID_HEXSZ;
	len -= GIT_OID_HEXSZ;

	if (len && line[0] == ' ') {
		line++;
		len--;

		if (!git__prefixncmp(line, len, "continue"))
			pkt->status = GIT_ACK_CONTINUE;
		else if (!git__prefixncmp(line, len, "common"))
			pkt->status = GIT_ACK_COMMON;
		else if (!git__prefixncmp(line, len, "ready"))
			pkt->status = GIT_ACK_READY;
		else
			goto out_err;
	}

	*out = (git_pkt *) pkt;

	return 0;

out_err:
	git_error_set(GIT_ERROR_NET, "error parsing ACK pkt-line");
	git__free(pkt);
	return -1;
}