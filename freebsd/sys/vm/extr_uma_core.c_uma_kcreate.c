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
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  uma_keg_t ;
typedef  int /*<<< orphan*/  uma_init ;
typedef  int /*<<< orphan*/  uma_fini ;
typedef  int /*<<< orphan*/  uint32_t ;
struct uma_kctor_args {size_t size; int align; int /*<<< orphan*/  zone; int /*<<< orphan*/  flags; int /*<<< orphan*/  fini; int /*<<< orphan*/  uminit; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int UMA_ALIGN_CACHE ; 
 int /*<<< orphan*/  UMA_ANYDOMAIN ; 
 int /*<<< orphan*/  kegs ; 
 int uma_align_cache ; 
 int /*<<< orphan*/  zone_alloc_item (int /*<<< orphan*/ ,struct uma_kctor_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uma_keg_t
uma_kcreate(uma_zone_t zone, size_t size, uma_init uminit, uma_fini fini,
		int align, uint32_t flags)
{
	struct uma_kctor_args args;

	args.size = size;
	args.uminit = uminit;
	args.fini = fini;
	args.align = (align == UMA_ALIGN_CACHE) ? uma_align_cache : align;
	args.flags = flags;
	args.zone = zone;
	return (zone_alloc_item(kegs, &args, UMA_ANYDOMAIN, M_WAITOK));
}