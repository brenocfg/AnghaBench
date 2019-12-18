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
typedef  int /*<<< orphan*/  VideoState ;

/* Variables and functions */
 int get_master_sync_type (int /*<<< orphan*/ *) ; 

int ffp_get_master_sync_type(VideoState *is)
{
    return get_master_sync_type(is);
}