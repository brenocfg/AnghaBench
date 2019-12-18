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
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 struct evbuffer* bufferevent_get_input (int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int evbuffer_remove (struct evbuffer*,char*,int) ; 

__attribute__((used)) static int
bio_bufferevent_read(BIO *b, char *out, int outlen)
{
	int r = 0;
	struct evbuffer *input;

	BIO_clear_retry_flags(b);

	if (!out)
		return 0;
	if (!BIO_get_data(b))
		return -1;

	input = bufferevent_get_input(BIO_get_data(b));
	if (evbuffer_get_length(input) == 0) {
		/* If there's no data to read, say so. */
		BIO_set_retry_read(b);
		return -1;
	} else {
		r = evbuffer_remove(input, out, outlen);
	}

	return r;
}