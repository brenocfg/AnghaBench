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
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_rangehigh; int /*<<< orphan*/  ml_rangelow; int /*<<< orphan*/  ml_auxsingle; int /*<<< orphan*/  ml_single; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAC_LOMAC_FLAG_AUX ; 
 int MAC_LOMAC_FLAG_RANGE ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 int lomac_element_to_string (struct sbuf*,int /*<<< orphan*/ *) ; 
 int sbuf_putc (struct sbuf*,char) ; 

__attribute__((used)) static int
lomac_to_string(struct sbuf *sb, struct mac_lomac *ml)
{

	if (ml->ml_flags & MAC_LOMAC_FLAG_SINGLE) {
		if (lomac_element_to_string(sb, &ml->ml_single) == -1)
			return (EINVAL);
	}

	if (ml->ml_flags & MAC_LOMAC_FLAG_AUX) {
		if (sbuf_putc(sb, '[') == -1)
			return (EINVAL);

		if (lomac_element_to_string(sb, &ml->ml_auxsingle) == -1)
			return (EINVAL);

		if (sbuf_putc(sb, ']') == -1)
			return (EINVAL);
	}

	if (ml->ml_flags & MAC_LOMAC_FLAG_RANGE) {
		if (sbuf_putc(sb, '(') == -1)
			return (EINVAL);

		if (lomac_element_to_string(sb, &ml->ml_rangelow) == -1)
			return (EINVAL);

		if (sbuf_putc(sb, '-') == -1)
			return (EINVAL);

		if (lomac_element_to_string(sb, &ml->ml_rangehigh) == -1)
			return (EINVAL);

		if (sbuf_putc(sb, ')') == -1)
			return (EINVAL);
	}

	return (0);
}