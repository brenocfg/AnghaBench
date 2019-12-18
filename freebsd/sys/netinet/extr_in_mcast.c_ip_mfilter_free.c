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
struct in_mfilter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INMFILTER ; 
 int /*<<< orphan*/  free (struct in_mfilter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imf_purge (struct in_mfilter*) ; 

void
ip_mfilter_free(struct in_mfilter *imf)
{

	imf_purge(imf);
	free(imf, M_INMFILTER);
}