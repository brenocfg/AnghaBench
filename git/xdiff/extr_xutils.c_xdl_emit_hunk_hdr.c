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
struct TYPE_4__ {scalar_t__ (* out_hunk ) (int /*<<< orphan*/ ,long,long,long,long,char const*,long) ;int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ xdemitcb_t ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,long,long,long,long,char const*,long) ; 
 int xdl_format_hunk_hdr (long,long,long,long,char const*,long,TYPE_1__*) ; 

int xdl_emit_hunk_hdr(long s1, long c1, long s2, long c2,
		      const char *func, long funclen,
		      xdemitcb_t *ecb) {
	if (!ecb->out_hunk)
		return xdl_format_hunk_hdr(s1, c1, s2, c2, func, funclen, ecb);
	if (ecb->out_hunk(ecb->priv,
			  c1 ? s1 : s1 - 1, c1,
			  c2 ? s2 : s2 - 1, c2,
			  func, funclen) < 0)
		return -1;
	return 0;
}