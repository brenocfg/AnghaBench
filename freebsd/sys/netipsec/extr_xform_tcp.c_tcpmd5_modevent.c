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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  tcpmd5_methods ; 
 int /*<<< orphan*/  tcpmd5_support_disable () ; 
 int /*<<< orphan*/  tcpmd5_support_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpsignature_xformsw ; 
 int /*<<< orphan*/  xform_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xform_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tcpmd5_modevent(module_t mod, int type, void *data)
{

	switch (type) {
	case MOD_LOAD:
		xform_attach(&tcpsignature_xformsw);
#ifdef KLD_MODULE
		tcpmd5_support_enable(&tcpmd5_methods);
#endif
		break;
	case MOD_UNLOAD:
#ifdef KLD_MODULE
		tcpmd5_support_disable();
#endif
		xform_detach(&tcpsignature_xformsw);
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}