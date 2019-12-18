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
struct rss_config {struct rss_config* rss_bucket_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct rss_config*) ; 

void
rss_config_free(struct rss_config *rc)
{

	if ((rc != NULL) && rc->rss_bucket_map)
		free(rc->rss_bucket_map);
	if (rc != NULL)
		free(rc);
}