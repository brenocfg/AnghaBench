#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; char* error; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_err ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  GIT_PKT_ERR ; 
 TYPE_1__* git__malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int sideband_error_pkt(git_pkt **out, const char *line, size_t len)
{
	git_pkt_err *pkt;
	size_t alloc_len;

	line++;
	len--;

	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, sizeof(git_pkt_err), len);
	GIT_ERROR_CHECK_ALLOC_ADD(&alloc_len, alloc_len, 1);
	pkt = git__malloc(alloc_len);
	GIT_ERROR_CHECK_ALLOC(pkt);

	pkt->type = GIT_PKT_ERR;
	pkt->len = (int)len;
	memcpy(pkt->error, line, len);
	pkt->error[len] = '\0';

	*out = (git_pkt *)pkt;

	return 0;
}