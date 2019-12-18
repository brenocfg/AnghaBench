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
struct icode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct block {TYPE_1__ s; } ;

/* Variables and functions */
 scalar_t__ BPF_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_RET ; 
 struct block* JF (struct block*) ; 
 struct block* JT (struct block*) ; 
 int /*<<< orphan*/  Mark (struct icode*,struct block*) ; 
 int /*<<< orphan*/  isMarked (struct icode*,struct block*) ; 

__attribute__((used)) static void
make_marks(struct icode *ic, struct block *p)
{
	if (!isMarked(ic, p)) {
		Mark(ic, p);
		if (BPF_CLASS(p->s.code) != BPF_RET) {
			make_marks(ic, JT(p));
			make_marks(ic, JF(p));
		}
	}
}