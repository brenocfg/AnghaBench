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
typedef  int u8 ;
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/ * word; } ;
struct kvm_s390_gisa {TYPE_1__ u64; } ;

/* Variables and functions */
 int EBUSY ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int cmpxchg (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline int gisa_set_iam(struct kvm_s390_gisa *gisa, u8 iam)
{
	u64 word, _word;

	do {
		word = READ_ONCE(gisa->u64.word[0]);
		if ((u64)gisa != word >> 32)
			return -EBUSY;
		_word = (word & ~0xffUL) | iam;
	} while (cmpxchg(&gisa->u64.word[0], word, _word) != word);

	return 0;
}