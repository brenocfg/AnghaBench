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
struct io_state {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int io_pad (struct io_state*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ io_print (struct io_state*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
io_printandpad(struct io_state *iop, const CHAR *p, const CHAR *ep,
	       int len, const CHAR * __restrict with, locale_t locale)
{
	int p_len;

	p_len = ep - p;
	if (p_len > len)
		p_len = len;
	if (p_len > 0) {
		if (io_print(iop, p, p_len, locale))
			return (-1);
	} else {
		p_len = 0;
	}
	return (io_pad(iop, len - p_len, with, locale));
}