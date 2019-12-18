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
struct ngp_hdr {int dummy; } ;
struct ngp_fifo {int dummy; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/ * ngp_zone ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * uma_zcreate (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngp_modevent(module_t mod, int type, void *unused)
{
	int error = 0;

	switch (type) {
	case MOD_LOAD:
		ngp_zone = uma_zcreate("ng_pipe", max(sizeof(struct ngp_hdr),
		    sizeof (struct ngp_fifo)), NULL, NULL, NULL, NULL,
		    UMA_ALIGN_PTR, 0);
		if (ngp_zone == NULL)
			panic("ng_pipe: couldn't allocate descriptor zone");
		break;
	case MOD_UNLOAD:
		uma_zdestroy(ngp_zone);
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}