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
struct dpp_global {int /*<<< orphan*/  bootstrap; } ;
struct dpp_bootstrap_info {int /*<<< orphan*/  list; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpp_next_id (struct dpp_global*) ; 
 struct dpp_bootstrap_info* dpp_parse_qr_code (char const*) ; 

struct dpp_bootstrap_info * dpp_add_qr_code(struct dpp_global *dpp,
					    const char *uri)
{
	struct dpp_bootstrap_info *bi;

	if (!dpp)
		return NULL;

	bi = dpp_parse_qr_code(uri);
	if (!bi)
		return NULL;

	bi->id = dpp_next_id(dpp);
	dl_list_add(&dpp->bootstrap, &bi->list);
	return bi;
}