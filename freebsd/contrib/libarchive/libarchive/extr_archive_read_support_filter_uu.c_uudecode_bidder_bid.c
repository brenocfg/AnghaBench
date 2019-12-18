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
struct archive_read_filter_bidder {int dummy; } ;
struct archive_read_filter {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int UUDECODE (int /*<<< orphan*/ ) ; 
 size_t UUENCODE_BID_MAX_READ ; 
 unsigned char* __archive_read_filter_ahead (struct archive_read_filter*,int,scalar_t__*) ; 
 scalar_t__* base64 ; 
 scalar_t__ bid_get_line (struct archive_read_filter*,unsigned char const**,scalar_t__*,scalar_t__*,scalar_t__*,size_t*) ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 
 scalar_t__* uuchar ; 

__attribute__((used)) static int
uudecode_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *filter)
{
	const unsigned char *b;
	ssize_t avail, ravail;
	ssize_t len, nl;
	int l;
	int firstline;
	size_t nbytes_read;

	(void)self; /* UNUSED */

	b = __archive_read_filter_ahead(filter, 1, &avail);
	if (b == NULL)
		return (0);

	firstline = 20;
	ravail = avail;
	nbytes_read = avail;
	for (;;) {
		len = bid_get_line(filter, &b, &avail, &ravail, &nl, &nbytes_read);
		if (len < 0 || nl == 0)
			return (0); /* No match found. */
		if (len - nl >= 11 && memcmp(b, "begin ", 6) == 0)
			l = 6;
		else if (len -nl >= 18 && memcmp(b, "begin-base64 ", 13) == 0)
			l = 13;
		else
			l = 0;

		if (l > 0 && (b[l] < '0' || b[l] > '7' ||
		    b[l+1] < '0' || b[l+1] > '7' ||
		    b[l+2] < '0' || b[l+2] > '7' || b[l+3] != ' '))
			l = 0;

		b += len;
		avail -= len;
		if (l)
			break;
		firstline = 0;

		/* Do not read more than UUENCODE_BID_MAX_READ bytes */
		if (nbytes_read >= UUENCODE_BID_MAX_READ)
			return (0);
	}
	if (!avail)
		return (0);
	len = bid_get_line(filter, &b, &avail, &ravail, &nl, &nbytes_read);
	if (len < 0 || nl == 0)
		return (0);/* There are non-ascii characters. */
	avail -= len;

	if (l == 6) {
		/* "begin " */
		if (!uuchar[*b])
			return (0);
		/* Get a length of decoded bytes. */
		l = UUDECODE(*b++); len--;
		if (l > 45)
			/* Normally, maximum length is 45(character 'M'). */
			return (0);
		if (l > len - nl)
			return (0); /* Line too short. */
		while (l) {
			if (!uuchar[*b++])
				return (0);
			--len;
			--l;
		}
		if (len-nl == 1 &&
		    (uuchar[*b] ||		 /* Check sum. */
		     (*b >= 'a' && *b <= 'z'))) {/* Padding data(MINIX). */
			++b;
			--len;
		}
		b += nl;
		if (avail && uuchar[*b])
			return (firstline+30);
	} else if (l == 13) {
		/* "begin-base64 " */
		while (len-nl > 0) {
			if (!base64[*b++])
				return (0);
			--len;
		}
		b += nl;

		if (avail >= 5 && memcmp(b, "====\n", 5) == 0)
			return (firstline+40);
		if (avail >= 6 && memcmp(b, "====\r\n", 6) == 0)
			return (firstline+40);
		if (avail > 0 && base64[*b])
			return (firstline+30);
	}

	return (0);
}