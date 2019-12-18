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
struct tar {int dummy; } ;
struct archive_read {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int int64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_WARN ; 
 int INT64_MAX ; 
 scalar_t__ readline (struct archive_read*,struct tar*,char const**,scalar_t__,size_t*) ; 
 scalar_t__ tar_min (int,int) ; 

__attribute__((used)) static int64_t
gnu_sparse_10_atol(struct archive_read *a, struct tar *tar,
    int64_t *remaining, size_t *unconsumed)
{
	int64_t l, limit, last_digit_limit;
	const char *p;
	ssize_t bytes_read;
	int base, digit;

	base = 10;
	limit = INT64_MAX / base;
	last_digit_limit = INT64_MAX % base;

	/*
	 * Skip any lines starting with '#'; GNU tar specs
	 * don't require this, but they should.
	 */
	do {
		bytes_read = readline(a, tar, &p,
			(ssize_t)tar_min(*remaining, 100), unconsumed);
		if (bytes_read <= 0)
			return (ARCHIVE_FATAL);
		*remaining -= bytes_read;
	} while (p[0] == '#');

	l = 0;
	while (bytes_read > 0) {
		if (*p == '\n')
			return (l);
		if (*p < '0' || *p >= '0' + base)
			return (ARCHIVE_WARN);
		digit = *p - '0';
		if (l > limit || (l == limit && digit > last_digit_limit))
			l = INT64_MAX; /* Truncate on overflow. */
		else
			l = (l * base) + digit;
		p++;
		bytes_read--;
	}
	/* TODO: Error message. */
	return (ARCHIVE_WARN);
}