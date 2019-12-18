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
struct sbuf {int dummy; } ;
struct mac_mls {int mm_flags; int /*<<< orphan*/  mm_rangehigh; int /*<<< orphan*/  mm_rangelow; int /*<<< orphan*/  mm_effective; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAC_MLS_FLAG_EFFECTIVE ; 
 int MAC_MLS_FLAG_RANGE ; 
 int mls_element_to_string (struct sbuf*,int /*<<< orphan*/ *) ; 
 int sbuf_putc (struct sbuf*,char) ; 

__attribute__((used)) static int
mls_to_string(struct sbuf *sb, struct mac_mls *mm)
{

	if (mm->mm_flags & MAC_MLS_FLAG_EFFECTIVE) {
		if (mls_element_to_string(sb, &mm->mm_effective) == -1)
			return (EINVAL);
	}

	if (mm->mm_flags & MAC_MLS_FLAG_RANGE) {
		if (sbuf_putc(sb, '(') == -1)
			return (EINVAL);

		if (mls_element_to_string(sb, &mm->mm_rangelow) == -1)
			return (EINVAL);

		if (sbuf_putc(sb, '-') == -1)
			return (EINVAL);

		if (mls_element_to_string(sb, &mm->mm_rangehigh) == -1)
			return (EINVAL);

		if (sbuf_putc(sb, ')') == -1)
			return (EINVAL);
	}

	return (0);
}