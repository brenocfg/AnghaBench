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
struct tty {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  cnputsn (char const*,int) ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/ * panicstr ; 
 int tty_putstrn (struct tty*,char const*,int) ; 

__attribute__((used)) static int
sbuf_tty_drain(void *a, const char *d, int len)
{
	struct tty *tp;
	int rc;

	tp = a;

	if (kdb_active) {
		cnputsn(d, len);
		return (len);
	}
	if (tp != NULL && panicstr == NULL) {
		rc = tty_putstrn(tp, d, len);
		if (rc != 0)
			return (-ENXIO);
		return (len);
	}
	return (-ENXIO);
}