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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_init (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_free (scalar_t__) ; 

__attribute__((used)) static int
bio_bufferevent_free(BIO *b)
{
	if (!b)
		return 0;
	if (BIO_get_shutdown(b)) {
		if (BIO_get_init(b) && BIO_get_data(b))
			bufferevent_free(BIO_get_data(b));
		BIO_free(b);
	}
	return 1;
}