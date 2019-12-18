#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  packs; int /*<<< orphan*/  url; } ;

/* Variables and functions */
#define  HTTP_MISSING_TARGET 129 
#define  HTTP_OK 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int http_get_info_packs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ push_verbosely ; 
 TYPE_1__* repo ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int fetch_indices(void)
{
	int ret;

	if (push_verbosely)
		fprintf(stderr, "Getting pack list\n");

	switch (http_get_info_packs(repo->url, &repo->packs)) {
	case HTTP_OK:
	case HTTP_MISSING_TARGET:
		ret = 0;
		break;
	default:
		ret = -1;
	}

	return ret;
}