#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * url; } ;
typedef  TYPE_1__ git_proxy_options ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (char*) ; 

void git_proxy_options_clear(git_proxy_options *opts)
{
	git__free((char *) opts->url);
	opts->url = NULL;
}