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
typedef  int /*<<< orphan*/  zio_cksum_t ;
struct TYPE_3__ {int /*<<< orphan*/  zcs_bytes; } ;
typedef  TYPE_1__ zio_cksum_salt_t ;
typedef  void Skein_512_Ctxt_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  Skein_512_InitExt (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

void *
abd_checksum_skein_tmpl_init(const zio_cksum_salt_t *salt)
{
	Skein_512_Ctxt_t	*ctx;

	ctx = kmem_zalloc(sizeof (*ctx), KM_SLEEP);
	(void) Skein_512_InitExt(ctx, sizeof (zio_cksum_t) * 8, 0,
	    salt->zcs_bytes, sizeof (salt->zcs_bytes));
	return (ctx);
}