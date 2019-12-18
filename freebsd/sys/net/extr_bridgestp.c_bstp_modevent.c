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
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  bstp_list ; 
 int /*<<< orphan*/  bstp_list_mtx ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bstp_modevent(module_t mod, int type, void *data)
{
	switch (type) {
	case MOD_LOAD:
		mtx_init(&bstp_list_mtx, "bridgestp list", NULL, MTX_DEF);
		LIST_INIT(&bstp_list);
		break;
	case MOD_UNLOAD:
		mtx_destroy(&bstp_list_mtx);
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}