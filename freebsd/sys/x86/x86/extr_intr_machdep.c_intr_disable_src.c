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
struct intsrc {TYPE_1__* is_pic; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pic_disable_source ) (struct intsrc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PIC_EOI ; 
 int /*<<< orphan*/  stub1 (struct intsrc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intr_disable_src(void *arg)
{
	struct intsrc *isrc;

	isrc = arg;
	isrc->is_pic->pic_disable_source(isrc, PIC_EOI);
}