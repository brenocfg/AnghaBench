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
struct mac_lomac_proc {int dummy; } ;
struct label {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_LOMAC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 TYPE_1__* PSLOT (struct label*) ; 
 int /*<<< orphan*/  PSLOT_SET (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lomac_proc_init_label(struct label *label)
{

	PSLOT_SET(label, malloc(sizeof(struct mac_lomac_proc), M_LOMAC,
	    M_ZERO | M_WAITOK));
	mtx_init(&PSLOT(label)->mtx, "MAC/Lomac proc lock", NULL, MTX_DEF);
}