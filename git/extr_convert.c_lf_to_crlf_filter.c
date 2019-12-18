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
struct stream_filter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vtbl; } ;
struct lf_to_crlf_filter {TYPE_1__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  lf_to_crlf_vtbl ; 
 struct lf_to_crlf_filter* xcalloc (int,int) ; 

__attribute__((used)) static struct stream_filter *lf_to_crlf_filter(void)
{
	struct lf_to_crlf_filter *lf_to_crlf = xcalloc(1, sizeof(*lf_to_crlf));

	lf_to_crlf->filter.vtbl = &lf_to_crlf_vtbl;
	return (struct stream_filter *)lf_to_crlf;
}