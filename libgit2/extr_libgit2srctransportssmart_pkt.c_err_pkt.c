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
typedef  int /*<<< orphan*/  git_pkt_progress ;
struct TYPE_5__ {size_t len; char* error; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_err ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int /*<<< orphan*/  GIT_PKT_ERR ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 TYPE_1__* git__malloc (size_t) ; 
 scalar_t__ git__prefixncmp (char const*,size_t,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int err_pkt(git_pkt **out, const char *line, size_t len)
{
	git_pkt_err *pkt = NULL;
	size_t alloclen;

	/* Remove "ERR " from the line */
	if (git__prefixncmp(line, len, "ERR "))
		goto out_err;
	line += 4;
	len -= 4;

	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, sizeof(git_pkt_progress), len);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, alloclen, 1);
	pkt = git__malloc(alloclen);
	GIT_ERROR_CHECK_ALLOC(pkt);
	pkt->type = GIT_PKT_ERR;
	pkt->len = len;

	memcpy(pkt->error, line, len);
	pkt->error[len] = '\0';

	*out = (git_pkt *) pkt;

	return 0;

out_err:
	git_error_set(GIT_ERROR_NET, "error parsing ERR pkt-line");
	git__free(pkt);
	return -1;
}