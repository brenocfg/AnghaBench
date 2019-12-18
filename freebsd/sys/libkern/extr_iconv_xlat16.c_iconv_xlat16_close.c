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
struct kobj {int dummy; } ;
struct iconv_xlat16 {void* f_ctp; void* t_ctp; TYPE_1__* d_csp; } ;
struct TYPE_2__ {int /*<<< orphan*/  cp_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ICONV ; 
 int /*<<< orphan*/  iconv_close (void*) ; 
 int /*<<< orphan*/  kobj_delete (struct kobj*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iconv_xlat16_close(void *data)
{
	struct iconv_xlat16 *dp = data;

	if (dp->f_ctp && dp->f_ctp != data)
		iconv_close(dp->f_ctp);
	if (dp->t_ctp && dp->t_ctp != data)
		iconv_close(dp->t_ctp);
	dp->d_csp->cp_refcount--;
	kobj_delete((struct kobj*)data, M_ICONV);
	return (0);
}