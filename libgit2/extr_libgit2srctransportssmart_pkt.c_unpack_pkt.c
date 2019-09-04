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
struct TYPE_4__ {int unpack_ok; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_unpack ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_PKT_UNPACK ; 
 TYPE_1__* git__malloc (int) ; 
 int /*<<< orphan*/  git__prefixncmp (char const*,size_t,char*) ; 

__attribute__((used)) static int unpack_pkt(git_pkt **out, const char *line, size_t len)
{
	git_pkt_unpack *pkt;

	pkt = git__malloc(sizeof(*pkt));
	GIT_ERROR_CHECK_ALLOC(pkt);
	pkt->type = GIT_PKT_UNPACK;

	if (!git__prefixncmp(line, len, "unpack ok"))
		pkt->unpack_ok = 1;
	else
		pkt->unpack_ok = 0;

	*out = (git_pkt *)pkt;
	return 0;
}