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
typedef  int /*<<< orphan*/  tmp ;
struct archive_string {int dummy; } ;
typedef  int /*<<< orphan*/  sec ;
typedef  int /*<<< orphan*/  nanos ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_pax_attr (struct archive_string*,char const*,char*) ; 
 char* format_int (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_pax_attr_time(struct archive_string *as, const char *key,
    int64_t sec, unsigned long nanos)
{
	int digit, i;
	char *t;
	/*
	 * Note that each byte contributes fewer than 3 base-10
	 * digits, so this will always be big enough.
	 */
	char tmp[1 + 3*sizeof(sec) + 1 + 3*sizeof(nanos)];

	tmp[sizeof(tmp) - 1] = 0;
	t = tmp + sizeof(tmp) - 1;

	/* Skip trailing zeros in the fractional part. */
	for (digit = 0, i = 10; i > 0 && digit == 0; i--) {
		digit = nanos % 10;
		nanos /= 10;
	}

	/* Only format the fraction if it's non-zero. */
	if (i > 0) {
		while (i > 0) {
			*--t = "0123456789"[digit];
			digit = nanos % 10;
			nanos /= 10;
			i--;
		}
		*--t = '.';
	}
	t = format_int(t, sec);

	add_pax_attr(as, key, t);
}