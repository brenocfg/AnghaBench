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
typedef  int /*<<< orphan*/  git_pkt_progress ;
struct TYPE_4__ {size_t len; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_data ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,int,size_t) ; 
 int /*<<< orphan*/  GIT_PKT_DATA ; 
 TYPE_1__* git__malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int data_pkt(git_pkt **out, const char *line, size_t len)
{
	git_pkt_data *pkt;
	size_t alloclen;

	line++;
	len--;

	GIT_ERROR_CHECK_ALLOC_ADD(&alloclen, sizeof(git_pkt_progress), len);
	pkt = git__malloc(alloclen);
	GIT_ERROR_CHECK_ALLOC(pkt);

	pkt->type = GIT_PKT_DATA;
	pkt->len = len;
	memcpy(pkt->data, line, len);

	*out = (git_pkt *) pkt;

	return 0;
}