#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct walker {scalar_t__ get_verbosely; } ;
struct alt_base {int got_indices; char* base; int /*<<< orphan*/  packs; } ;

/* Variables and functions */
#define  HTTP_MISSING_TARGET 129 
#define  HTTP_OK 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int http_get_info_packs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int fetch_indices(struct walker *walker, struct alt_base *repo)
{
	int ret;

	if (repo->got_indices)
		return 0;

	if (walker->get_verbosely)
		fprintf(stderr, "Getting pack list for %s\n", repo->base);

	switch (http_get_info_packs(repo->base, &repo->packs)) {
	case HTTP_OK:
	case HTTP_MISSING_TARGET:
		repo->got_indices = 1;
		ret = 0;
		break;
	default:
		repo->got_indices = 0;
		ret = -1;
	}

	return ret;
}